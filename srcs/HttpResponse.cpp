#include "HttpResponse.hpp"

HttpResponse::HttpResponse() : _status_code(200) {
	setHeader("Server", "Webserv/1.0");
}

HttpResponse::~HttpResponse() {}

std::string HttpResponse::_getStatusMessage(int code) const {
	switch (code) {
		case 200: return "OK";
		case 201: return "Created";
		case 204: return "No Content";
		case 301: return "Moved Permanently";
		case 400: return "Bad Request";
		case 403: return "Forbidden";
		case 404: return "Not Found";
		case 405: return "Method Not Allowed";
		case 413: return "Payload Too Large";
		case 500: return "Internal Server Error";
		case 502: return "Bad Gateway";
		default:  return "Unknown Error";
	}
}

int HttpResponse::getStatusCode() const {
	return _status_code;
}

void HttpResponse::setStatusCode(int code) {
	_status_code = code;
}

void HttpResponse::setHeader(const std::string& key, const std::string& value) {
	_headers[key] = value;
}

void HttpResponse::setBody(const std::string& content) {
	_body = content;

	std::stringstream ss;
	ss << _body.size();
	setHeader("Content-Length", ss.str());
}

std::string HttpResponse::getRawResponse() const {
	std::stringstream res;

	res << "Http/1.0 " << _status_code << " " << _getStatusMessage(_status_code) << "\r\n";
	
	for (std::map<std::string, std::string>::const_iterator it = _headers.begin(); it != _headers.end(); ++it) {
		res << it->first << ": " << it->second << "\r\n";
	}

	res << "\r\n";
	res << _body;

	return res.str();
}

void HttpResponse::setContentType(const std::string& path) {
	std::string ext = "";
	size_t pos = path.find_last_of(".");

	if (pos != std::string::npos) {
		ext = path.substr(pos);
	}

	if (ext == ".html" || ext == ".htm")
		setHeader("Content-Type", "text/html");
	else if (ext == ".css")
		setHeader("Content-Type", "text/css");
	else if (ext == ".js")
		setHeader("Content-Type", "application/javascript");
	else if (ext == ".png")
		setHeader("Content-Type", "image/png");
	else if (ext == ".jpg" || ext == ".jpeg")
		setHeader("Content-Type", "image/jpeg");
	else if (ext == ".gif")
		setHeader("Content-Type", "image/gif");
	else
		setHeader("Content-Type", "text/plain");
}

void HttpResponse::generateErrorPage(int code, const ServerConfig& config) {
	setStatusCode(code);
	
	std::map<int, std::string>::const_iterator it = config.error_pages.find(code);
	
	if (it != config.error_pages.end()) {
		std::ifstream file(it->second.c_str());

		if (file.is_open()) {
			std::stringstream buffer;
			buffer << file.rdbuf();
			setBody(buffer.str());
			setHeader("Content-Type", "text/html");
			return ;
		}
	}

	std::stringstream ss;
	ss << "<html><body><h1>Error " << code << "</h1><p>" 
	<< _getStatusMessage(code) << "</p></body></html>";
	setBody(ss.str());
	setHeader("Content-Type", "text/html");
}
