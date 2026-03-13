#pragma once

#include <map>
#include <string>
#include <sstream>
#include <iostream>

class HttpRequest {
	private:
		size_t								_contentLength;
		std::string							_method;
		std::string							_uri;
		std::string							_query;
		std::string							_protocol;
		std::string							_body;
		std::map<std::string, std::string>	_headers;
	
	public:
		HttpRequest();
		~HttpRequest();

		bool				parse(const std::string& rawRequest);

		const size_t&		getContentLength() const {return _contentLength; };
		const std::string&	getMethod() const { return _method; };
		const std::string&	getPath() const { return _uri; };
		const std::string&	getQuery() const { return _query; };
		const std::string&	getProtocol() const { return _protocol; };
		const std::string&	getBody() const { return _body; };
		std::string			getCookie(const std::string& key) const;
		//int					getError() const { return _error; };

		void				setMethod(std::string token);
		void				setContentLength(std::string token);
};
