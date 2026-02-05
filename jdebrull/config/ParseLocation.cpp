/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseLocation.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 12:37:43 by jdebrull          #+#    #+#             */
/*   Updated: 2026/02/05 16:48:42 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseLocation.hpp"

static bool	isValidMethod(const std::string& token) {
	return (token == "GET" || token == "POST" || token == "DELETE");
}

static void	parseMethods(std::vector<std::string>& tokens, size_t& i, Location& loc)
{
	i++;
	if (i >= tokens.size())
		throw (std::runtime_error("Missing directive for the allowed_methods in location directive."));
	while (i < tokens.size() && tokens[i] != ";")
	{
		if (!isValidMethod(tokens[i]))
			throw (std::runtime_error("Unkown method for location directive."));
		if (loc.methods.count(tokens[i]))
			throw (std::runtime_error("Duplicate method in allowed methods."));
		loc.methods.insert(tokens[i]);
		i++;
	}
	if (loc.methods.empty())
		throw (std::runtime_error("Need at least one allowed method."));
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ';' after allowed methods."));
	i++;
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

void	parseUpload(std::vector<std::string>& tokens, size_t& i, Location& loc)
{
	if (!loc.upload.empty())
		throw (std::runtime_error("Duplicate upload directives."));
	i++;
	if (i >= tokens.size() || tokens[i] == ";")
		throw (std::runtime_error("Missing path for upload directive."));
	if (!isValidPath(tokens[i]))
		throw (std::runtime_error("Path is invalid for upload directive."));
	loc.upload = tokens[i];
	i++;
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ; after upload directive path."));
	i++;
}

static int	isValidReturnCode(const std::string& token)
{
	if (token.empty())
		throw (std::runtime_error("Status Code is required for return directive."));
	int	n = 0;
	for (size_t i = 0; i < token.size(); ++i)
	{
		char c = token[i];
		if (!isDigit(c))
			throw (std::runtime_error("Only numbers are allowed for the return status code."));
		n = (n * 10) + (c -'0');
		if (n > 599)
			throw (std::runtime_error("Return Status code is not in the right range [100,599]."));
	}
	if (n < 100)
		throw (std::runtime_error("Return Status code is not in the right range [100,599]."));
	return (n);
}

void	parseReturn(std::vector<std::string>& tokens, size_t& i, Location& loc)
{
	i++;
	if (i >= tokens.size() || tokens[i] == ";")
		throw (std::runtime_error("Missing status code for the return directive."));

	int code = isValidReturnCode(tokens[i]);
	i++;

	std::string path;
	if (i < tokens.size() && tokens[i][0] == '/')
	{
		if (!isValidErrorCodePath(tokens[i]))
			throw (std::runtime_error("Invalid path for return directive."));
		
		path = tokens[i];
		i++;
	}
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ';' after return directive path."));
	i++;
	loc.return_code = code;
	loc.return_url = path;
}

bool	isValidCgiPath(const std::string& token)
{
	if (token.empty())
		return (false);
	if (token.find("..") != std::string::npos)
		return (false);
	for (size_t i = 0; i < token.size(); ++i)
	{
		char c = token[i];
		if (!isAlNum(c) && c != '/' && c != '_' && c != '-' && c != '.')
			return (false);
	}
	return (true);
}

void parseCgiExtension(std::vector<std::string>& tokens, size_t& i, Location& loc)
{
	i++; 
	if (i >= tokens.size() || tokens[i] == ";")
		throw (std::runtime_error("Missing extension for the CGI extension directive."));
	std::string ext = tokens[i];
	if (ext.empty() || ext[0] != '.')
		throw (std::runtime_error("CGI extension must start with a dot."));
	i++;
	if (i >= tokens.size())
		throw (std::runtime_error("Missing path for cgi_extension directive."));
	std::string cgi_path = tokens[i];

	if (!isValidCgiPath(cgi_path))
		throw (std::runtime_error("Invalid path for cgi_extension directive."));
	i++;
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ';' after cgi_extension directive."));
	i++;
	if (loc.cgi_extension.count(ext))
		throw (std::runtime_error("Duplicate cgi_extension directive for the same extension."));
	loc.cgi_extension[ext] = cgi_path;
}

static void	finalizeLocation(Location& loc, const Server& serv)
{
	if (loc.root.empty())
		loc.root = serv.root;
	if (loc.index.empty())
		loc.index = serv.index;
	if (loc.methods.empty())
		loc.methods.insert("GET");
}

void	parseLocation(std::vector<std::string>& tokens, size_t& i, Server&  serv)
{
	Location loc;
	i++;
	if (i >= tokens.size() || tokens[i] == ";" || tokens[i] == "{")
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
		if (tokens[i] == "methods")
			parseMethods(tokens, i, loc);
		else if (tokens[i] == "root") {
			parseRoot(tokens, i, loc.root);
		}
		else if (tokens[i] == "index") {
			parseIndex(tokens, i, loc.index, loc.index_set);
		}
		else if (tokens[i] == "autoindex")
			parseAutoIndex(tokens, i, loc);
		else if (tokens[i] == "client_max_size")
			parseMaxSize(tokens, i, loc.client_max_size, 52428800); //50MB
		else if (tokens[i] == "upload")
			parseUpload(tokens, i, loc);
		else if (tokens[i] == "return")
			parseReturn(tokens, i, loc);
		else if (tokens[i] == "cgi_extension")
			parseCgiExtension(tokens, i, loc);
		else if (tokens[i] == ";")
			throw (std::runtime_error("No ';' are allowed to be left unsupervised."));
		else
			throw std::runtime_error("Unknown directive in location block: " + tokens[i]);
	}
	if (i >= tokens.size() || tokens[i] != "}")
		throw (std::runtime_error("Expected '}' at end of location block."));
	i++;
	finalizeLocation(loc, serv);
	serv.locations.push_back(loc);
}