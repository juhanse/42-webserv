#pragma once

#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include "Config.hpp"
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <sstream>

class ResponseGenerator {
	private:
		HTTPResponse _handleStatic(const HTTPRequest& req, const Location& loc, const ServerConfig& config);
		HTTPResponse _handleCGI(const HTTPRequest& req, const Location& loc);
		HTTPResponse _handleDelete(const std::string& fullPath);

		const Location* _matchLocation(const std::string& requestPath, const ServerConfig& config);
		std::string _readFile(const std::string& path);

	public:
		ResponseGenerator();
		~ResponseGenerator();

		HTTPResponse generate(const HTTPRequest& req, const ServerConfig& config);
};
