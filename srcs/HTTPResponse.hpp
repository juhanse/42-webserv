#pragma once

#include "Config.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

class HTTPResponse {
	private:
		int									_status_code;
		std::string							_body;
		std::map<std::string, std::string>	_headers;
		static std::map<int, std::string>	_status_messages;
		static std::map<int, std::string>	_initStatusMessages();

	public:
		HTTPResponse();
		~HTTPResponse();

		void setStatusCode(int code);
		void setHeader(const std::string& key, const std::string& value);
		void setBody(const std::string& content);

		// Helpers
		void setContentType(const std::string& path); // MIME type
		void generateErrorPage(int code, const ServerConfig& config);

		// La méthode main -> Antonia
		std::string getRawResponse() const; 
};
