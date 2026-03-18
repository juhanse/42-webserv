/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebserverSignals.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:55:41 by ade-woel          #+#    #+#             */
/*   Updated: 2026/03/18 13:55:42 by ade-woel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "Webserver.hpp"

void	signalHandler(int sig) {
	(void)sig;
	g_shutdown = 1;
}

void Webserver::setUpSignals() const {
	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);
	signal(SIGQUIT, signalHandler);
	signal(SIGPIPE, SIG_IGN);
}

void	Webserver::cleanup() {
	std::cout << "\nShutting down server..." << std::endl;

	for (std::map<int, Client*>::iterator it = _clients.begin(); 
		it != _clients.end(); ++it) {
			std::cout << "Closing client " << it->first << std::endl;
			delete it->second;
			close(it->first);
		}
		_clients.clear();
	
	for (std::map<int, ServerConfig*>::iterator it = _listenFds.begin();
		 it != _listenFds.end(); ++it) {
		
		std::cout << "Closing listen socket " << it->first << std::endl;
		close(it->first);
	}
	_listenFds.clear();

	_pollWatch.clear();

	std::cout << "Server stopped" << std::endl;
}
