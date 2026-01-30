/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:53:13 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/30 19:10:23 by jdebrull         ###   ########.fr       */
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

void	parseLocation(std::vector<std::string>& tokens, size_t& i, Server& serv)
{
	
}

void	parseTokens(std::vector<std::string> tokens, std::vector<Server>& servers)
{
	size_t	i = 0;

	while (i < tokens.size())
	{
		if (tokens[i] != "server")
			throw (std::runtime_error("Expected 'server'"));
		i++;
		if (i >= tokens.size() || tokens[i] != "{")
			throw std::runtime_error("Expected '{'");
		i++;
		
		Server	serv;
		
		while (i < tokens.size() && tokens[i] != "}")
		{	
			if (tokens[i] == "listen")
			{
				i++;
				if (i >= tokens.size())
                    throw std::runtime_error("Expected value after listen");
				parseListen(tokens[i], serv);
				i++;
				if (i >= tokens.size() || tokens[i] != ";")
					throw (std::runtime_error("Garbage value after the Ip adress and port."));
				i++;
			}
			else if (tokens[i] == "server_name") {
				parseServerName(tokens, i, serv);
			} 
			else if (tokens[i] == "root") {
				parseRoot(tokens, i, serv);
			}
			else if (tokens[i] == "index") {
				parseIndex(tokens, i, serv);
			}
			else if (tokens[i] == "client_max_body_size") {
				parseBodySize(tokens, i, serv);
			}
			else if (tokens[i] == "error_page") {
				parseErrorPage(tokens, i, serv);
			}
			else if (tokens[i] == "location") {
				parseLocation(tokens, i, serv);
			}
			else
				throw (std::runtime_error("Unkown directive : " + tokens[i]));
		}
		if (i >= tokens.size() || tokens[i] != "}")
			throw std::runtime_error("Expected '}' at end of server block");
		i++;
		servers.push_back(serv);
	}
}

std::vector<Server> ConfigParser::parse(const std::string& filename){
	std::vector<Server>	servers;
	
	std::ifstream	file(filename.c_str());
	if (!file.is_open())
		throw std::runtime_error("Cannot open config file.");
	
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string content = buffer.str();
		
	// std::cout << content << std::endl;

	std::vector<std::string> tokens = tokenize(content);
	
	// for (size_t i = 0; i < tokens.size(); ++i)
	// 	std::cout << "[" << tokens[i] << "]" << std::endl;

	parseTokens(tokens, servers);
	
	return (servers);
}
