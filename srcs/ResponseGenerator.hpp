#pragma once

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "ServerConfig.hpp"
#include <string>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>

class ResponseGenerator {
	private:
		const Location* _matchLocation(const std::string& requestPath, const ServerConfig& config);
		std::string		_readFile(const std::string& path);
		char**			_createCGIEnv(const HttpRequest& req, const Location& loc, const std::string& scriptPath);
        void			_freeEnv(char** envp);

		HttpResponse _handleStatic(const HttpRequest& req, const Location& loc, const ServerConfig& config);
		HttpResponse _handleCGI(const HttpRequest& req, const Location& loc, const ServerConfig& config);
		HttpResponse _handleDelete(const HttpRequest& req, const Location& loc, const ServerConfig& config);
		HttpResponse _handlePostUpload(const HttpRequest& req, const Location& loc, const ServerConfig& config);

	public:
		ResponseGenerator();
		~ResponseGenerator();

		HttpResponse generate(const HttpRequest& req, const ServerConfig& config);
};
