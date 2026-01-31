/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseLocation.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 12:37:43 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/31 15:49:43 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseLocation.hpp"

static bool	isValidMethod(const std::string& token) {
	return (token == "GET" || token == "POST" || token == "DELETE");
}

static void	parseAllowedMethods(std::vector<std::string>& tokens, size_t& i, Location& loc)
{
	i++;
	if (i >= tokens.size())
		throw (std::runtime_error("Missing directive for the allowed_methods in location directive."));
	while (i < tokens.size() && tokens[i] != ";")
	{
		if (!isValidMethod(tokens[i]))
			throw (std::runtime_error("Unkown method for location directive."));
		if (loc.allowed_methods.count(tokens[i]))
			throw (std::runtime_error("Duplicate method in allowed_methods."));
		loc.allowed_methods.insert(tokens[i]);
		i++;
	}
	if (loc.allowed_methods.empty())
		throw (std::runtime_error("Need at least one allowed method."));
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ';' after allowed methods."));
	i++;
}

static bool isValidPath(const std::string& token)
{
	if (token.empty())
		return (false);
	if (token[0] != '/')
		return (false);
	for (size_t i = 0; i < token.size(); ++i)
	{
		char c = token[i];
		if (!isAlNum(c) && c != '/' && c != '_' && c != '-' && c != '.'
			&& c != '%' && c != '~' && c != '+')
			return (false);
	}
	return (true);
}

void	parseAutoIndex(std::vector<std::string>& tokens, size_t& i, Location& loc)
{
	if (loc.autoindex_set)
		throw (std::runtime_error("Only one autoindex directive is allowed per location block."));
	
	i++;
	if (i >= tokens.size() || tokens[i] == ";")
		throw (std::runtime_error("Missing a value for autoindex directive."));
	if (tokens[i] == "on")
		loc.autoindex = true;
	else if (tokens[i] == "off")
		loc.autoindex = false;
	else
		throw (std::runtime_error("Wrong directive for autoindex either 'on' or 'off'."));
	
	loc.autoindex_set = true;
	
	i++;
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ';' after autoindex directive."));
	i++;
}

void	parseLocation(std::vector<std::string>& tokens, size_t& i, Server&  serv)
{
	Location loc;
	i++;
	if (i >= tokens.size() || tokens[i] == ";")
		throw (std::runtime_error("Expected path for location directive."));
	if (!isValidPath(tokens[i]))
		throw (std::runtime_error("Invalid path for location directive."));
	loc.path = tokens[i];
	i++;
	if (i >= tokens.size() || tokens[i] != "{")
		throw (std::runtime_error("Expected '{' after path for location directive."));
	i++;
	while (i < tokens.size() && tokens[i] != "}")
	{
		if (tokens[i] == "allowed_methods")
			parseAllowedMethods(tokens, i, loc);
		else if (tokens[i] == "root") {
			parseRoot(tokens, i, loc.root);
		}
		else if (tokens[i] == "index") {
			parseIndex(tokens, i, loc.index);
		}
		else if (tokens[i] == "autoindex")
			parseAutoIndex(tokens, i, loc);
		else if (tokens[i] == "client_max_size")
			parseMaxSize(tokens, i, loc.client_max_size, 52428800); //50MB
		else if (tokens[i] == ";")
			throw (std::runtime_error("No ';' are allowed to be left unsupervised."));
		else
			throw std::runtime_error("Unknown directive in location block.");
	}
	if (i >= tokens.size() || tokens[i] != "}")
		throw (std::runtime_error("Expected '}' at end of location block."));
	i++;
	serv.locations.push_back(loc);
}