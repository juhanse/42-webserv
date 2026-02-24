#pragma once

#include <string>
#include <map>
#include <sstream>

class HTTPRequest {
	private:
		std::string							_method;
		std::string							_path;
		std::string							_query;
		std::string							_protocol;
		std::string							_body;
		std::map<std::string, std::string>	_headers;

	public:
		HTTPRequest();
		~HTTPRequest();

		void parse(const std::string& rawData);

		const std::string& getMethod() const { return _method; };
		const std::string& getPath() const { return _path; };
		const std::string& getQuery() const { return _query; };
		const std::string& getProtocol() const { return _protocol; };
		const std::string& getBody() const { return _body; };
};