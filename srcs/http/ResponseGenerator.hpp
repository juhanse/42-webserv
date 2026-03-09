#pragma once

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "../config/ServerConfig.hpp"
#include "../config/LocationConfig.hpp"
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <cstdio>

class ResponseGenerator {
	private:
		const LocationConfig* _matchLocation(const std::string& requestPath, const ServerConfig& config);
		std::string _readFile(const std::string& path);

		HttpResponse _handleStatic(const HttpRequest& req, const LocationConfig& loc, const ServerConfig& config);
		HttpResponse _handleCGI(const HttpRequest& req, const LocationConfig& loc, const ServerConfig& config);
		HttpResponse _handleDelete(const HttpRequest& req, const LocationConfig& loc, const ServerConfig& config);
		HttpResponse _handlePostUpload(const HttpRequest& req, const LocationConfig& loc, const ServerConfig& config);

	public:
		ResponseGenerator();
		~ResponseGenerator();

		HttpResponse generate(const HttpRequest& req, const ServerConfig& config);
};
