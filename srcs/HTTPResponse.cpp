#include "HTTPResponse.hpp"

HTTPResponse::HTTPResponse() {}
HTTPResponse::~HTTPResponse() {}

std::map<int, std::string> HTTPResponse::_status_messages = HTTPResponse::_initStatusMessages();

std::map<int, std::string> HTTPResponse::_initStatusMessages() {
    std::map<int, std::string> m;

    m[200] = "OK";
    m[201] = "Created";
    m[204] = "No Content";
    m[301] = "Moved Permanently";
    m[400] = "Bad Request";
    m[403] = "Forbidden";
    m[404] = "Not Found";
    m[405] = "Method Not Allowed";
    m[413] = "Payload Too Large";
    m[500] = "Internal Server Error";
    m[502] = "Bad Gateway";

    return m;
}

std::string HTTPResponse::getRawResponse() const {
    std::stringstream res;
    // On récupère le message correspondant au code
    std::string msg = _status_messages.count(_status_code) ? _status_messages.at(_status_code) : "Unknown Error";

    res << "HTTP/1.1 " << _status_code << " " << msg << "\r\n";
    // ... suite des headers et body
    return res.str();
}

void HTTPResponse::setStatusCode(int code) {
    _status_code = code;
}

void HTTPResponse::setHeader(const std::string& key, const std::string& value) {
    _headers[key] = value;
}

void HTTPResponse::setBody(const std::string& content) {
    _body = content;

    // Conversion de la taille en string (C++98 style)
    std::stringstream ss;
    ss << _body.size();
    
    // On met à jour le header indispensable pour le navigateur
    setHeader("Content-Length", ss.str());
}
