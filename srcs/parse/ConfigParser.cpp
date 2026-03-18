/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:49:05 by jdebrull          #+#    #+#             */
/*   Updated: 2026/03/18 13:49:05 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConfigParser.hpp"

std::vector<std::string> ConfigParser::tokenize(const std::string& input)
{
	std::vector<std::string> tokens;
	std::string token;
	
	for (size_t i = 0; i < input.size(); ++i)
	{
		char  c = input[i];

		if (c == '#') {
			while (i < input.size() && input[i] != '\n')
				i++;
			continue ;
		}
		if (std::isspace(c))
		{
			if (!token.empty())
			{
				tokens.push_back(token);
				token.clear();
			}
		}
		else if (c == '{' || c == '}' || c == ';')
		{
			if (!token.empty())
			{
				tokens.push_back(token);
				token.clear();
			}
			tokens.push_back(std::string(1, c));
		}
		else {
			token += c;
		}
	}
	if (!token.empty())
		tokens.push_back(token);
	return (tokens);
}

void	parseTokens(std::vector<std::string>& tokens, std::vector<ServerConfig>& servers)
{
	size_t	i = 0;
	while (i < tokens.size())
	{
		if (tokens[i] != "server")
			throw (std::runtime_error("Expected 'server' at: " + tokens[i]));
		i++;
		if (i >= tokens.size() || tokens[i] != "{")
			throw std::runtime_error("Expected '{'");
		i++;

		ServerConfig		serv;
		bool				listen_set = false;
		bool				index_set = false;
		bool				root_set = false;

		while (i < tokens.size() && tokens[i] != "}")
		{
			if (tokens[i] == "listen") {
				parseListen(tokens, i, serv, listen_set);
			}
			else if (tokens[i] == "server_name") {
				parseServerName(tokens, i, serv);
			}
			else if (tokens[i] == "root") {
				parseRoot(tokens, i, serv, root_set);
			}
			else if (tokens[i] == "index") {
				parseIndex(tokens, i, serv, index_set);
			}
			else if (tokens[i] == "client_max_body_size") {
				parseMaxSize(tokens, i, serv, 52428800); //50MB
			}
			else if (tokens[i] == "error_page") {
				parseErrorPage(tokens, i, serv);
			}
			else if (tokens[i] == "location") {
				parseLocation(tokens, i, serv);
			}
			else if (tokens[i] == ";")
				throw (std::runtime_error("No ';' are allowed to roam the file aimelessly."));
			else
				throw (std::runtime_error("Unknown directive : " + tokens[i]));
		}
		if (i >= tokens.size() || tokens[i] != "}")
			throw std::runtime_error("Expected '}' at end of server block");
		i++;
		servers.push_back(serv);
	}
}

static void	checkMissingDirectives(std::vector<ServerConfig>& servers)
{
	for (size_t i = 0; i < servers.size(); ++i)
	{
		if (servers[i].getPort() == 0)
			throw (std::runtime_error("Missing Listen directive in server block."));
		if (servers[i].getRoot().empty())
			throw (std::runtime_error("Missing root directive in server block."));
	}
}

static void	checkDuplicatePort(std::vector<ServerConfig>& servers)
{
	std::set<int> ports;

	for (size_t i = 0; i < servers.size(); ++i)
	{
		int port = servers[i].getPort();
		if (ports.count(port))
			throw (std::runtime_error("Duplicate ports in different server blocs "));
		ports.insert(port);
	}
}

std::vector<ServerConfig> ConfigParser::parse(const std::string& filename)
{
	std::vector<ServerConfig>	servers;

	std::ifstream	file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Cannot open config file.");

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string content = buffer.str();

	if (content.empty())
		throw (std::runtime_error("Incomplete config file."));

	std::vector<std::string> tokens = tokenize(content);

	parseTokens(tokens, servers);
	checkMissingDirectives(servers);
	checkDuplicatePort(servers);
	return (servers);
}
