/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.42belgium.be>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:55:23 by ade-woel          #+#    #+#             */
/*   Updated: 2026/03/18 22:55:13 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserver.hpp"
#include "parse/ConfigParser.hpp"
#include "config/ServerConfig.hpp"
#include "http/ResponseGenerator.hpp"

volatile sig_atomic_t g_shutdown = 0;

int	main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Usage: ./webserv [configuration file]" << std::endl;
		return (1);
	}

	std::vector<ServerConfig> servers;
	std::vector<ServerConfig*> configurations;

	try {
		ConfigParser parser;

		servers = parser.parse(av[1]);
	
		std::cout << "Configuration file is valid" << std::endl;
	}
	catch (const std::exception &e) {
		std::cerr << "Config error: " << e.what() << std::endl;
		return (1);
	}

	for (size_t i = 0; i < servers.size(); i++) {
		configurations.push_back(&servers[i]);
	}

	Webserver	webserv(configurations);

	for (size_t i = 0; i < configurations.size(); i++) {
		if (webserv.newServ(configurations[i]) == -1) {
			std::cerr << "Servers couldn't init" << std::endl;
			return (1);
		}
	}

	webserv.runServ();

	return (0);
}
