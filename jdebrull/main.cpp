/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:21:26 by Jdebrull          #+#    #+#             */
/*   Updated: 2026/02/18 16:37:08 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config/ConfigParser.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr	<< "Use ./webserv config.conf " << std::endl;
		return (1);
	}
	try
	{
		ConfigParser parser;
		std::vector<Server> servers = parser.parse(av[1]);
	
		std::cout << "No errors detected in parsing." << std::endl;
		printServers(servers);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Config error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}