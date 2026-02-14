#pragma once

#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include "Config.hpp"
#include <string>
#include <sys/stat.h> // Pour stat()
#include <fstream>
#include <sstream>

class ResponseGenerator {
    public:
        ResponseGenerator();
        ~ResponseGenerator();

        // Point d'entrée unique pour ton module
        HTTPResponse generate(const HTTPRequest& req, const ServerConfig& config);

    private:
        // Les trois piliers de ton module
        HTTPResponse _handleStatic(const HTTPRequest& req, const Location& loc);
        HTTPResponse _handleCGI(const HTTPRequest& req, const Location& loc);
        HTTPResponse _handleDelete(const std::string& fullPath);

        // Utilitaires internes
        Location    _matchLocation(const std::string& requestPath, const ServerConfig& config);
        std::string _readFile(const std::string& path);
        std::string _identifyContentType(const std::string& path);
};
