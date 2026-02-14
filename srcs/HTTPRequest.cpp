#include "HTTPRequest.hpp"

HTTPRequest::HTTPRequest() {}
HTTPRequest::~HTTPRequest() {}

void HTTPRequest::parse(const std::string& rawData) {
    std::istringstream stream(rawData);
    std::string line;

    // 1. Parsing de la première ligne (ex: GET /index.html?id=1 HTTP/1.1)
    if (std::getline(stream, line)) {
        std::istringstream lineStream(line);
        lineStream >> _method >> _path >> _protocol;

        // Extraction de la query string (après le ?)
        size_t questionMarkPos = _path.find('?');
        if (questionMarkPos != std::string::npos) {
            _query = _path.substr(questionMarkPos + 1);
            _path = _path.substr(0, questionMarkPos);
        }
    }

    // 2. Parsing des Headers
    while (std::getline(stream, line) && line != "\r" && !line.empty()) {
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            std::string key = line.substr(0, colonPos);
            std::string value = line.substr(colonPos + 2); // +2 pour sauter ": "
            // Nettoyage du \r à la fin si présent
            if (!value.empty() && value[value.size() - 1] == '\r')
                value.erase(value.size() - 1);
            _headers[key] = value;
        }
    }

    // 3. Le reste est le corps (Body)
    std::stringstream bodyStream;
    bodyStream << stream.rdbuf();
    _body = bodyStream.str();
}

const std::string& HTTPRequest::getMethod() const { return _method; }
const std::string& HTTPRequest::getPath() const { return _path; }
const std::string& HTTPRequest::getQuery() const { return _query; }
const std::string& HTTPRequest::getProtocol() const { return _protocol; }
const std::string& HTTPRequest::getBody() const { return _body; }
