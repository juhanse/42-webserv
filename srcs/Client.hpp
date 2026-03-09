#pragma once

#include <iostream>
#include "http/HttpRequest.hpp"
#include "http/HttpResponse.hpp"
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
		// int			_port;
		// std::string	_ip;
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
		bool		isCompleted();
		void		resetActivity();

	public:
		Client(int fd);
		~Client();

		int			getStatus() const;
		bool		hasTimedOut() const;
		void		readRequest();
		void		processRequest();
		void		writeResponse();
};
