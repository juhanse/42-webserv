#pragma once

#include <iostream>

class HttpRequest;

class Client {
	private:
		int				_fd;
		// int			_port;
		// std::string	_ip;
		// time_t		_lastActive;
		//Status		_status;

		std::string		_recvBuff;
		std::string		_sendBuff;

		//HttpRequest*	_request;
		//HttpResponse*	_response;

		//ServerConfig*	_config;


	public:
		Client(int fd);
		~Client();

		enum Status {
		READING,
		PROCESSING,
		WRITING,
		DONE
		};

};


