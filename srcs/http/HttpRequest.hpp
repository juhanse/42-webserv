#pragma once

#include <string>
#include <map>
#include <sstream>

class HttpRequest {
	private:
		size_t								_contentLength;
		std::string							_method;
		std::string							_path;
		std::string							_query;
		std::string							_protocol;
		std::string							_body;
		std::map<std::string, std::string>	_headers;

	public:
		HttpRequest();
		~HttpRequest();

		void parse(const std::string& rawData);

		const size_t&		getContentLength() const {return _contentLength; };
		const std::string&	getMethod() const { return _method; };
		const std::string&	getPath() const { return _path; };
		const std::string&	getQuery() const { return _query; };
		const std::string&	getProtocol() const { return _protocol; };
		const std::string&	getBody() const { return _body; };
		std::string 		getHeader(const std::string& key) const;

		void				setMethod(std::string token);
		void				setContentLength(std::string token);

};
