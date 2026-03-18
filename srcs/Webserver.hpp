/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:55:32 by ade-woel          #+#    #+#             */
/*   Updated: 2026/03/18 13:55:33 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <vector>
#include <poll.h>
#include <fcntl.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include "Client.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include "config/ServerConfig.hpp"

class	Webserver {
	private:
		struct CgiData {
			Client* client;
			pid_t pid;
			time_t startTime;
			std::string output;
		};
	
		std::vector<pollfd>				_pollWatch;		//array of fds under poll's watch
		std::vector<ServerConfig*>		_configs;		//array of server configs
		std::map<int, Client*>			_clients;		//key: Client connect fd ; value: associated Client
		std::map<int, ServerConfig*>	_listenFds;		//key: Server listen fd ; value: associated config
		
		std::map<int, CgiData> 			_cgiMap;
		
		void	cleanup();
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

		void	registerCgi(Client* client, int pipeFd, pid_t pid);
		void	readCgi(int fd);
		void	handleCgiEnd(int fd);
		void	checkCgiTimeouts();
		void	removeFromPollWatch(int fd);

	public:
		Webserver(std::vector<ServerConfig*>);
		~Webserver();

		int		newServ(ServerConfig* config);
		void	runServ();
		void	setUpSignals() const;
};

extern volatile sig_atomic_t g_shutdown;
