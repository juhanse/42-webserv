#pragma once

#include <iostream>
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include <sstream>
#include <sys/socket.h>

#define TIMEOUT 60

enum Status {
	READING,
	PROCESSING,
	WRITING,
	DONE
};

enum Method {
	GET,
	POST,
	DELETE,
	UNKNOWN
};

class	Client {
	private:
		int				_fd;
		time_t			_lastActive;

		Status			_status;
		std::string		_recvBuff;
		std::string		_sendBuff;
		size_t			_sendOffset;

		HttpRequest*	_request;
		HttpResponse*	_response;

		ServerConfig*	_config;

		bool		bodyIsFull(size_t bodyStart, size_t expectedBody) const;
 		int			findMethod() const;
		bool		findContentLength(std::string headers);
		void		handleRequest();
		bool		isCompleted();
		bool		parseRequest();
		bool		parseRequestLine();
		void		resetActivity();

	public:
		Client(int fd);
		~Client();

		int			getStatus() const {return _status; };
		bool		hasTimedOut() const;
		void		readRequest();
		void		processRequest();
		void		writeResponse();
};
