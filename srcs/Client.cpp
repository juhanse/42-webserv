#include "Client.hpp"

Client::Client(int fd, ServerConfig* config):	_fd(fd), 
												_lastActive(time(NULL)),
												_status(READING),
												_recvBuff(""),
												_sendBuff(""),
												_sendOffset(0),
												_config(config)
{
	_request = new HttpRequest();
	_response = new HttpResponse();
}

Client::~Client() {
	delete	_request;
	delete	_response;
}

void	Client::resetActivity() {
	_lastActive = time(NULL);
}

bool	Client::hasTimedOut() const {
	return (time(NULL) - _lastActive > TIMEOUT);
}

bool	Client::bodyIsFull(size_t bodyStart, size_t expectedBody) const {
	size_t	currentBody = _recvBuff.size() - bodyStart;
	if (currentBody < expectedBody)
		return (false);
	return (true);
}

int	Client::findMethod() const {
	if (_recvBuff.compare(0, 4, "GET ") == 0)
		return (GET);
	if (_recvBuff.compare(0, 7, "DELETE ") == 0)
		return (DELETE);
	if (_recvBuff.compare(0, 5, "POST ") == 0)
		return (POST);
	else
		return (UNKNOWN);
}

bool	Client::findContentLength(std::string headers) {
	std::string	lowerCase = headers;
	for(size_t i = 0; i < lowerCase.size(); i++)
		lowerCase[i] = std::tolower(lowerCase[i]);

	size_t	clTag = lowerCase.find("content-length:");
	if (clTag == std::string::npos) {
		std::cout << "Content-Length header is missing" << std::endl;
		return (false);
	}
	else {
		std::string			value;
		std::string			postCl = lowerCase.substr(clTag + 15);
		std::stringstream	ss(postCl);
		ss >> value;

		if (!value.empty()) {
			for (size_t i = 0; i < value.size(); i++) {
				if (!std::isdigit(value[i])) {
					std::cout << "Wrong value in content length" << std::endl;
					return (false);
				}
			}
			_request->setContentLength(value);
			std::cout << "Content Length is: " << _request->getContentLength() << std::endl;
			return (true);
		}
		return (false);
	}
}

bool	Client::isCompleted() {
	size_t		endTag = _recvBuff.find("\r\n\r\n");
	if (endTag == std::string::npos)
		return (false);

	int 		method = findMethod();
	std::string	headers;

	switch (method) {
		case GET:
			std::cout << "GET detected" << std::endl;
			return (true);
		case DELETE:
			return (true);
		case POST:
			std::cout << "POST detected" << std::endl;
			headers = _recvBuff.substr(0, endTag);
			if (!findContentLength(headers))
				return (_response->setStatusCode(400), true); //Length missing 400 vs 411?

			if (_request->getContentLength() > _config->getClientMaxBodysize())
				return (_response->setStatusCode(413), true); //400 vs 413 Payload too large?

			if (bodyIsFull(endTag + 4, _request->getContentLength()))
				return (true);
			
			return (false);	
		case UNKNOWN:
		default:
			//more precise detection? 405 vs 501
			std::cout << "Unknown request type" << std::endl;
			return(_response->setStatusCode(405), true);
	}
}

void	Client::handleRequest() {
	ResponseGenerator	generator;
	HttpResponse		res = generator.generate(*_request, *_config);

	*_response = res;
}

void	Client::processRequest() {
	int	code = _response->getStatusCode();

	if (code >= 400)
		_response->generateErrorPage(code, *_config);
 
	else {
		if (_request->parse(_recvBuff))
			handleRequest();
		else {
			_response->setStatusCode(400);
			_response->generateErrorPage(_response->getStatusCode(), *_config);
		}
	}
	_status = WRITING;
}

void	Client::readRequest() {
	char	buffer[4096];

	ssize_t	bytes = recv(_fd, buffer, sizeof(buffer), 0);

	if (bytes == 0) {
		std::cout << "Client " << _fd << " closed connection" << std::endl;
		_status = DONE;
	}
	else if (bytes > 0) {
		resetActivity();
		_recvBuff.append(buffer, bytes);

		if (isCompleted()) {
			_status = PROCESSING;
			std::cout 	<< "RECEIVED REQUEST:\n"
						<<_recvBuff << std::endl;
		}
	}
	else {
		perror("recv()");
		_status = DONE;
	}
}

void	Client::writeResponse() {
	if (_sendBuff.empty()) {
		_sendBuff = _response->getRawResponse();
		_sendOffset = 0;
	}

	size_t	leftover = _sendBuff.size() - _sendOffset;
	size_t	bytes = send(_fd, _sendBuff.c_str(), leftover, 0);

	if (bytes > 0) {
		_sendOffset += bytes;
		resetActivity();

		if (_sendOffset >= _sendBuff.size()) {
			std::cout << "Response sent" << std::endl;
			_status = DONE;
		}
	}

	else if (bytes == 0)
		_status = DONE;
	
	else {
		perror("send()");
		_status = DONE;
	}
}

void	Client::parseCgiOutput(const std::string& output, int code) {
	if (code != 200) {
		_response->generateErrorPage(code, *_config);
		_status = WRITING;
		return;
	}

	size_t headerEnd = output.find("\r\n\r\n");
	if (headerEnd != std::string::npos) {
		std::string headers = output.substr(0, headerEnd);
		std::string body = output.substr(headerEnd + 4);
		
		size_t ctPos = headers.find("Content-Type: ");
		if (ctPos != std::string::npos) {
			size_t ctEnd = headers.find("\r\n", ctPos);
			if (ctEnd == std::string::npos) ctEnd = headers.length();
			std::string ct = headers.substr(ctPos + 14, ctEnd - (ctPos + 14));
			_response->setHeader("Content-Type", ct);
		}
		_response->setBody(body);
	} else {
		_response->setBody(output);
	}

	_response->setStatusCode(200);
	_status = WRITING;
}
