#include "HttpRequest.hpp"

HttpRequest::HttpRequest() {}

HttpRequest::~HttpRequest() {}

void	HttpRequest::setMethod(std::string token) {
	_method = token;
}

void	HttpRequest::setContentLength(std::string token) {
	std::stringstream	ss(token);
	ss >> _contentLength;
}
