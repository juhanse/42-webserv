#include "HttpRequest.hpp"

HttpRequest::HttpRequest(): _contentLength(0),
							_method(""),
							_uri(""),
							_query(""),
							_protocol(""),
							_body(""),
							_headers() {}

HttpRequest::~HttpRequest() {}

void	HttpRequest::setMethod(std::string token) {
	_method = token;
}

void	HttpRequest::setContentLength(std::string token) {
	std::stringstream	ss(token);
	ss >> _contentLength;
}

std::string HttpRequest::getCookie(const std::string& key) const {
	std::string cookieHeader = getHeader("Cookie");
	if (cookieHeader.empty()) {
		return "";
	}

	std::string search = key + "=";
	size_t pos = cookieHeader.find(search);
	if (pos == std::string::npos) {
		return "";
	}

	pos += search.length();
	size_t end = cookieHeader.find(";", pos);
	if (end == std::string::npos) {
		end = cookieHeader.length();
	}

	return cookieHeader.substr(pos, end - pos);
}

bool	HttpRequest::parse(const std::string& rawRequest) {
	std::istringstream stream(rawRequest);
	std::string line;

	if (std::getline(stream, line)) {
		if (line.empty())
			return (false);
		std::istringstream lineStream(line);
		lineStream >> _method >> _uri >> _protocol;

		if (_method.empty() || _uri.empty() || _protocol.empty())
			return (false);

		std::string	leftover;
		if (lineStream >> leftover)
			return (false);

		if (_uri.find("..") != std::string::npos)
			return (false);

		size_t questionMarkPos = _uri.find('?');
		if (questionMarkPos != std::string::npos) {
			_query = _uri.substr(questionMarkPos + 1);
			_uri = _uri.substr(0, questionMarkPos);
		}

		if (_protocol != "HTTP/1.0" && _protocol != "HTTP/1.1")
			return (false);
	}
	else
		return (false);

	while (std::getline(stream, line) && line != "\r" && !line.empty()) {
		size_t tag = line.find(':');
		if (tag != std::string::npos) {
			std::string key = line.substr(0, tag);
			std::string value = line.substr(tag + 2);
			
			if (key.find(" ") != std::string::npos || key.empty())
				return (false);

			if (!value.empty() && value[value.size() - 1] == '\r') {
				value.erase(value.size() - 1);
			}
			_headers[key] = value;
		}
		else
			return (false);
	}

	std::stringstream bodyStream;
	bodyStream << stream.rdbuf();
	_body = bodyStream.str();

	return (true);
}

std::string HttpRequest::getHeader(const std::string& key) const {
	std::map<std::string, std::string>::const_iterator it = _headers.find(key);

	if (it != _headers.end()) {
		return it->second;
	}

	return ""; 
}
