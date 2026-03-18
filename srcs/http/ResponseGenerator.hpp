/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseGenerator.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:58:59 by juhanse           #+#    #+#             */
/*   Updated: 2026/03/18 13:59:00 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "../config/ServerConfig.hpp"
#include "../config/LocationConfig.hpp"
#include "../session/SessionManager.hpp"
#include <string>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>

class ResponseGenerator {
	private:
		const LocationConfig* 	_matchLocation(const std::string& requestPath, const ServerConfig& config);
		std::string				_readFile(const std::string& path);
		std::string 			_getScriptDirectory(const std::string& scriptPath);
		char**					_createCGIEnv(const HttpRequest& req, const std::string& scriptPath);
        void					_freeEnv(char** envp);

		HttpResponse			_handleGET(const HttpRequest& req, const LocationConfig& loc, const ServerConfig& config);
		HttpResponse			_handlePOST(const HttpRequest& req, const LocationConfig& loc, const ServerConfig& config);
		HttpResponse			_handleDELETE(const HttpRequest& req, const LocationConfig& loc, const ServerConfig& config);
		HttpResponse			_handleCGI(const HttpRequest& req, const LocationConfig& loc, const ServerConfig& config);
		HttpResponse			_handleUpload(const HttpRequest& req, const LocationConfig& loc, const ServerConfig& config, const std::string& boundary);

	public:
		ResponseGenerator();
		~ResponseGenerator();

		HttpResponse generate(const HttpRequest& req, const ServerConfig& config);
};
