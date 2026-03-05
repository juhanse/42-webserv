#pragma once

#include <map>
#include <vector>
#include <poll.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include "Client.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include "ServerConfig.hpp"

class	Webserver {
	private:
		std::vector<pollfd>				_pollWatch;		//array of fds under poll's watch
		std::vector<ServerConfig*>		_configs;		//array of server configs
		
		std::map<int, Client*>			_clients;		//key: Client connect fd ; value: associated Client
		std::map<int, ServerConfig*>	_listenFds;		//key: Server listen fd ; value: associated config

		void	closeClient(int fd);
		void	closeTimedOut();
		bool	isListenSock(int fd);
		void	newClient(int listFd);
		int		newListenSock(int port);
		void	receiveRequest(int fd);
		void	sendResponse(int fd);
		void	sendToWatchList(int fd);
		int		setNonBlock(int fd);
		void	switchToPollout(int fd);

	public:
		Webserver(std::vector<ServerConfig*>);
		~Webserver();

		int		newServ(ServerConfig* config);
		void	runServ();

};
