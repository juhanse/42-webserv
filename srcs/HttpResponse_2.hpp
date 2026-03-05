#pragma once

#include "ServerConfig.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>

class HttpResponse {
	private:
		int									_status_code;
		std::string							_body;
		std::map<std::string, std::string>	_headers;

		std::string _getStatusMessage(int code) const;

	public:
		HttpResponse();
		~HttpResponse();

		int getStatusCode() const;

		void setStatusCode(int code);
		void setHeader(const std::string& key, const std::string& value);
		void setBody(const std::string& content);

		void setContentType(const std::string& path);
		void generateErrorPage(int code, const ServerConfig& config);

		std::string getRawResponse() const; 
};
