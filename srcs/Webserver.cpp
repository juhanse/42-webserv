/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserver.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:55:27 by ade-woel          #+#    #+#             */
/*   Updated: 2026/03/18 23:53:32 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserver.hpp"

Webserver::Webserver(std::vector<ServerConfig*> configs): _configs(configs) {}

Webserver::~Webserver() {
	cleanup();
}

int	Webserver::newListenSock(int port) {
	int	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		return (perror("socket()"), -1);
	
	int	option = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1)
		return (perror("setsockopt()"), close(fd), -1);
	
	if (setNonBlock(fd) == -1)
		return (close(fd), -1);
	
	struct sockaddr_in	addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(fd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) == -1)
		return (perror("bind()"), close(fd), -1);
	
	if (listen(fd, SOMAXCONN) == -1)
		return (perror("listen()"), close(fd), -1);
	
	return (fd);
}

void	Webserver::closeClient(int fd) {
	std::map<int, Client*>::iterator it_map = _clients.find(fd);
	if (it_map != _clients.end()) {
		delete it_map->second;
		_clients.erase(it_map);
	}

	for (std::vector<pollfd>::iterator it_vec = _pollWatch.begin();
			it_vec != _pollWatch.end() ; it_vec++) {
		if (it_vec->fd == fd) {
			_pollWatch.erase(it_vec);
			break ;
		}
	}
	std::cout << "Client " << fd << " disconnected" << std::endl;
	close(fd);
}

void	Webserver::newClient(int listFd) {
	struct sockaddr_in	client_addr;
	socklen_t sockLen = sizeof(client_addr);
	int	client_fd = accept(listFd, reinterpret_cast<sockaddr *>(&client_addr), &sockLen);
	if (client_fd == -1) {
		perror("accept()");
		return ;
	}

	if (setNonBlock(client_fd) == -1) {
		close(client_fd);
		return ;
	}

	Client*	client = new Client(client_fd, _listenFds[listFd]);
	_clients[client_fd] = client;

	sendToWatchList(client_fd);
	std::cout << "New client " << client_fd << " connected" << std::endl;
}

int Webserver::newServ(ServerConfig* config) {	
	int	listen_fd = newListenSock(config->getPort());

	if (listen_fd == -1) {
		std::cerr << "Listen socket creation failed on port " << config->getPort() << std::endl;
		return (-1);	
	}

	sendToWatchList(listen_fd);
	_listenFds[listen_fd] = config;	
	std::cout << "Server listening on port " << config->getPort() << "..." << std::endl;

	return (0);
}

void	Webserver::sendResponse(int fd) {
	std::map<int, Client*>::iterator it = _clients.find(fd);
	if (it == _clients.end())
		return ;

	Client* client = it->second;
	client->writeResponse();
	if (_clients[fd]->getStatus() == DONE)
		closeClient(fd);
}

void	Webserver::receiveRequest(int fd) {
	std::map<int, Client*>::iterator it = _clients.find(fd);
	if (it == _clients.end())
		return ;

	Client* client = it->second;
	if (client->getStatus() == DONE)
		closeClient(fd);

	if (client->getStatus() == READING)
		client->readRequest();

	if (client->getStatus() == PROCESSING) {
		client->processRequest();

		if (client->getResponse()->getStatusCode() == 100) {
            registerCgi(client, client->getResponse()->getCgiFdOut(), client->getResponse()->getCgiPid());
            return ;
        }
	}

	if (client->getStatus() == WRITING)
		switchToPollout(fd);
}

void	Webserver::runServ() {
	setUpSignals();

	while (g_shutdown == 0) {
		int isReady = poll(_pollWatch.data(), _pollWatch.size(), 3000);

		if (isReady == -1) {
			if (g_shutdown == 1)
				break ;
			perror("poll()");
			break ;
		}
	
		checkCgiTimeouts();

		if (isReady == 0) {
			closeTimedOut();
			continue ;
		}
		else {
			for (size_t i = 0; i < _pollWatch.size(); i++) {
				if (g_shutdown == 1)
					break ;

				int		fd = _pollWatch[i].fd;
				short	revents = _pollWatch[i].revents;
				bool	isListen = isListenSock(fd);
				bool 	isCgi = (_cgiMap.find(fd) != _cgiMap.end());

				if (!revents)
					continue ;

				if (revents & (POLLHUP | POLLERR | POLLNVAL)) {
					if (isCgi)
                    	handleCgiEnd(fd);
					else if (!isListen) {
						closeClient(fd);
						continue ;
					}
				}

				if (revents & POLLIN) {
					if (isListen)
						newClient(fd);
					else if (isCgi)
                    	readCgi(fd);
					else
						receiveRequest(fd);
				}
				else if (revents & POLLOUT)
					if (!isCgi)
						sendResponse(fd);
			}
		}
	}
}
