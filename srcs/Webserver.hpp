/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserver.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:48:25 by ade-woel          #+#    #+#             */
/*   Updated: 2026/02/24 12:57:29 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		std::vector<pollfd>				_pollWatch;		//un tableau de tous les fds a surveiller par poll()
		std::vector<ServerConfig*>		_configs;		//toutes les configs serveur detectees
		
		std::map<int, Client*>			_clients;		//key: connect fd ; value: Client associe
		std::map<int, ServerConfig*>	_listenFds;		//key: listen fd ; value: config associee

		int		newListenSock(int port);
		int		setNonBlock(int fd);
		bool	isListenSock(int fd);
		void	newClient(int listFd);
		void	closeClient(int fd);
		void	sendToWatchList(int fd); //pollWatchThis?

	public:
		Webserver(std::vector<ServerConfig*>);
		~Webserver();

		int		newServ(ServerConfig* config);
		void	runServ();

};
