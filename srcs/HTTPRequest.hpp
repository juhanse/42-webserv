#pragma once

#include <string>
#include <map>
#include <sstream>

class HTTPRequest {
    private:
        std::string                         _method;
        std::string                         _path;
        std::string                         _query;
        std::string                         _protocol;
        std::map<std::string, std::string>  _headers;
        std::string                         _body;

    public:
        HTTPRequest();
        ~HTTPRequest();

        // Fonction principale pour remplir l'objet
        void parse(const std::string& rawData);

        const std::string& getMethod() const;
        const std::string& getPath() const;
        const std::string& getQuery() const;
        const std::string& getProtocol() const;
        const std::string& getBody() const;

        void setMethod(std::string m) { _method = m; }
        void setPath(std::string p) { _path = p; }
};
