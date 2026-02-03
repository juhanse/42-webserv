/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugPrint.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:12:46 by jdebrull          #+#    #+#             */
/*   Updated: 2026/02/03 14:09:01 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debugPrint.hpp"

void printLocation(const Location &loc)
{
	std::cout << "    Location:" << std::endl;
	std::cout << "      path: " << loc.path << std::endl;

	if (!loc.root.empty())
		std::cout << "      root: " << loc.root << std::endl;

	if (!loc.index.empty())
	{
		std::cout << "      index:";
		for (size_t i = 0; i < loc.index.size(); i++)
			std::cout << " " << loc.index[i];
		std::cout << std::endl;
	}

	if (loc.autoindex_set)
		std::cout << "      autoindex: " << (loc.autoindex ? "on" : "off") << std::endl;

	if (!loc.methods.empty())
	{
		std::cout << "      allowed_methods:";
		for (std::set<std::string>::const_iterator it = loc.methods.begin();
			 it != loc.methods.end(); ++it)
			std::cout << " " << *it;
		std::cout << std::endl;
	}

	if (loc.client_max_size)
		std::cout << "      client_max_size: " << loc.client_max_size << std::endl;
}

void printServer(const Server &serv, size_t index)
{
	std::cout << "\nServer #" << index << std::endl;
	std::cout << "  host: " << serv.host << std::endl;
	std::cout << "  port: " << serv.port << std::endl;

	if (!serv.server_name.empty())
	{
		std::cout << "  server_name:";
		for (size_t i = 0; i < serv.server_name.size(); i++)
			std::cout << " " << serv.server_name[i];
		std::cout << std::endl;
	}

	if (!serv.root.empty())
		std::cout << "  root: " << serv.root << std::endl;

	if (!serv.index.empty())
	{
		std::cout << "  index:";
		for (size_t i = 0; i < serv.index.size(); i++)
			std::cout << " " << serv.index[i];
		std::cout << std::endl;
	}

	std::cout << "  client_max_body_size: " << serv.client_max_body_size << std::endl;

	if (!serv.error_page.empty())
	{
		std::cout << "  error_page:" << std::endl;
		for (std::map<int, std::string>::const_iterator it = serv.error_page.begin();
			 it != serv.error_page.end(); ++it)
			std::cout << "    " << it->first << " -> " << it->second << std::endl;
	}

	for (size_t i = 0; i < serv.locations.size(); i++)
		printLocation(serv.locations[i]);
}

void printServers(const std::vector<Server> &servers)
{
	for (size_t i = 0; i < servers.size(); i++)
		printServer(servers[i], i);
}