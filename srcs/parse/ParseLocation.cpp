/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseLocation.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:49:27 by jdebrull          #+#    #+#             */
/*   Updated: 2026/03/18 13:49:27 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseLocation.hpp"

static bool	isValidMethod(const std::string& token) {
	return (token == "GET" || token == "POST" || token == "DELETE");
}

static void	parseMethods(std::vector<std::string>& tokens, size_t& i, LocationConfig& loc)
{
	i++;
	if (i >= tokens.size())
		throw (std::runtime_error("Missing directive for the allowed_methods in location directive."));
	while (i < tokens.size() && tokens[i] != ";")
	{
		if (!isValidMethod(tokens[i]))
			throw (std::runtime_error("Unkown method for location directive."));

		loc.addMethod(tokens[i]);
		i++;
	}
	if (loc.getMethods().empty())
		throw (std::runtime_error("Need at least one allowed method."));
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ';' after allowed methods."));
	i++;
}

void	parseAutoIndex(std::vector<std::string>& tokens, size_t& i, LocationConfig& loc, bool& autoindex_set)
{
	if (autoindex_set)
		throw (std::runtime_error("Only one autoindex directive is allowed per location block."));
	
	i++;
	if (i >= tokens.size() || tokens[i] == ";")
		throw (std::runtime_error("Missing a value for autoindex directive."));
	if (tokens[i] == "on")
		loc.setAutoIndex(true);
	else if (tokens[i] == "off")
		loc.setAutoIndex(false);
	else
		throw (std::runtime_error("Wrong directive for autoindex either 'on' or 'off'."));
	
	autoindex_set = true;
	
	i++;
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ';' after autoindex directive."));
	i++;
}

void	parseUpload(std::vector<std::string>& tokens, size_t& i, LocationConfig& loc, bool& upload_set)
{
	if (upload_set)
		throw (std::runtime_error("Duplicate upload directives."));
	i++;
	if (i >= tokens.size() || tokens[i] == ";")
		throw (std::runtime_error("Missing path for upload directive."));
	if (!isValidPath(tokens[i]))
		throw (std::runtime_error("Path is invalid for upload directive."));
	loc.setUpload(tokens[i]);
	i++;
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ; after upload directive path."));
	upload_set = true;
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

static bool	isValidReturnPath(const std::string& token)
{
	if (token.empty())
		return (false);
	if (token[0] == '/' || token[0] == '.')
		return (true);
	if (token.find("http://") == 0 || token.find("https://") == 0)
		return (true);
	return (false);
}

void	parseReturn(std::vector<std::string>& tokens, size_t& i, LocationConfig& loc, bool& return_set)
{
	if (return_set)
		throw (std::runtime_error("Duplicate return directive."));
	i++;
	if (i >= tokens.size() || tokens[i] == ";")
		throw (std::runtime_error("Missing status code for the return directive."));

	int code = isValidReturnCode(tokens[i]);
	i++;

	std::string path;
	if (i < tokens.size() && tokens[i] != ";")
	{
		if (!isValidReturnPath(tokens[i]))
			throw (std::runtime_error("Invalid path for return directive."));

		path = tokens[i];
		i++;
	}
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ';' after return directive path."));
	i++;
	loc.setReturn(code, path);
	return_set = true;
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

void parseCgiExtension(std::vector<std::string>& tokens, size_t& i, LocationConfig& loc)
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
		throw (std::runtime_error("Invalid path for cgi_extension directive " + tokens[i]));
	
	i++;
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ';' after cgi_extension directive."));
	
	i++;
	loc.addCgiExtension(ext, cgi_path);
}

static void	finalizeLocation(LocationConfig& loc, const ServerConfig& serv, bool loc_root_set, bool loc_index_set)
{
	if (!loc_root_set)
		loc.setRoot(serv.getRoot());
	if (!loc_index_set)
	{
		const std::vector<std::string>& serverIndex = serv.getIndex();
	
		for (size_t j = 0; j < serverIndex.size(); ++j)
			loc.addIndex(serverIndex[j]);
	}
	if (loc.getMethods().empty())
		loc.addMethod("GET");
}

void	parseLocation(std::vector<std::string>& tokens, size_t& i, ServerConfig&  serv)
{
	LocationConfig loc;

	bool	root_set = false;
	bool	index_set = false;
	bool	autoindex_set = false;
	bool	upload_set = false;
	bool	return_set = false;

	i++;
	if (i >= tokens.size() || tokens[i] == ";" || tokens[i] == "{")
		throw (std::runtime_error("Expected path for location directive."));
	if (!isValidPath(tokens[i]))
		throw (std::runtime_error("Invalid path for location directive."));
	loc.setPath(tokens[i]);
	
	i++;
	if (i >= tokens.size() || tokens[i] != "{")
		throw (std::runtime_error("Expected '{' after path for location directive."));
	
	i++;
	while (i < tokens.size() && tokens[i] != "}")
	{
		if (tokens[i] == "allow_methods" || tokens[i] == "methods") {
			parseMethods(tokens, i, loc);
		}
		else if (tokens[i] == "root") {
			parseRoot(tokens, i, loc, root_set);
		}
		else if (tokens[i] == "index") {
			parseIndex(tokens, i, loc, index_set);
		}
		else if (tokens[i] == "autoindex")
			parseAutoIndex(tokens, i, loc, autoindex_set);
		else if (tokens[i] == "client_max_size" || tokens[i] == "client_max_body_size")
			parseMaxSize(tokens, i, loc, 52428800); //50MB
		else if (tokens[i] == "upload")
			parseUpload(tokens, i, loc, upload_set);
		else if (tokens[i] == "return")
			parseReturn(tokens, i, loc, return_set);
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
	finalizeLocation(loc, serv, root_set, index_set);
	serv.addLocation(loc);
}