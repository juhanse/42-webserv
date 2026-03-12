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

std::string	HttpRequest::getCookie(const std::string& key) const {
    std::map<std::string, std::string>::const_iterator it = _headers.find("Cookie");
    if (it != _headers.end()) {
        std::string cookies = it->second;
        size_t pos = cookies.find(key + "=");

        if (pos != std::string::npos) {
            size_t start = pos + key.length() + 1;
            size_t end = cookies.find(";", start);
	
            if (end == std::string::npos) {
                end = cookies.length();
            }
            return cookies.substr(start, end - start);
        }
    }
    return "";
}

void	HttpRequest::parse(const std::string& rawData) {
	std::istringstream stream(rawData);
	std::string line;

	if (std::getline(stream, line)) {
		std::istringstream lineStream(line);
		lineStream >> _method >> _path >> _protocol;

		size_t questionMarkPos = _path.find('?');
		if (questionMarkPos != std::string::npos) {
			_query = _path.substr(questionMarkPos + 1);
			_path = _path.substr(0, questionMarkPos);
		}
	}

	while (std::getline(stream, line) && line != "\r" && !line.empty()) {
		size_t colonPos = line.find(':');
		if (colonPos != std::string::npos) {
			std::string key = line.substr(0, colonPos);
			std::string value = line.substr(colonPos + 2);

			if (!value.empty() && value[value.size() - 1] == '\r') {
				value.erase(value.size() - 1);
			}
			_headers[key] = value;
		}
	}

	std::stringstream bodyStream;
	bodyStream << stream.rdbuf();
	_body = bodyStream.str();
}

void	HttpRequest::setMethod(std::string token) {
	_method = token;
}

void	HttpRequest::setContentLength(std::string token) {
	std::stringstream	ss(token);
	ss >> _contentLength;
}

std::string HttpRequest::getHeader(const std::string& key) const {
	std::map<std::string, std::string>::const_iterator it = _headers.find(key);

	if (it != _headers.end()) {
		return it->second;
	}

	return ""; 
}
