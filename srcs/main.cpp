/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-woel <ade-woel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:55:23 by ade-woel          #+#    #+#             */
/*   Updated: 2026/03/18 13:55:24 by ade-woel         ###   ########.fr       */
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

	try
	{
		ConfigParser parser;

		servers = parser.parse(av[1]);
	
		std::cout << "Configuration file is valid" << std::endl;
	}
	catch (const std::exception &e)
	{
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
