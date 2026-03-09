#include "Client.hpp"

Client::Client(int fd):	_fd(fd), 
						_lastActive(time(NULL)),
						_status(READING)
{
	_request = new HttpRequest();
	_response = new HttpResponse();
}

Client::~Client() {
	delete	_request;
	delete	_response;
}

int		Client::getStatus() const {
	return (_status);
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
				return (_response->setStatusCode(411), true); //Length missing 400 vs 411?
			// if (_request->getContentLength() > _config->client_max_body_size)
			// 	return (_response->setStatusCode(400), true); //400 vs 413 Payload too large?
			if (bodyIsFull(endTag + 4, _request->getContentLength()))
				return (true);
			return (false);	
		case UNKNOWN:
		default:
			//more precise detection? 405 vs 501
			std::cout << "Unknown request type" << std::endl;
			return(_response->setStatusCode(501), true);
	}
}

void	Client::processRequest() {
	//if (_response->getStatusCode() != 200)
		//generate response error + status WRITING

	//full parsing ici -> if parsing no error
		//handle request selon si GET, POST ou DELETE
	//else
		//status code aura ete maj dans le parsing 
		//generate response error

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
			//std::cout << _recvBuff << std::endl;
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
	size_t	bytes = send(_fd, _sendBuff.c_str(), leftover, 0); //check flags
}