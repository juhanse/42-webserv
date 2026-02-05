/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseIndex.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:09:08 by jdebrull          #+#    #+#             */
/*   Updated: 2026/02/05 16:52:38 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseIndex.hpp"

static bool	isDirective(const std::string& token)
{
	return ( token == "methods" || token == "root" || token == "index"
			|| token == "autoindex" || token == "client_max_size"
			|| token == "upload" || token == "return" || token == "cgi_extension");
}

static bool	isValidIndexFile(const std::string& token)
{
	if (token.empty())
		return (false);
		
	for (size_t i = 0; i < token.size(); i++)
	{
		char c = token[i];
		if (!isAlNum(c) && c != '.' && c != '-' && c != '_')
			return (false);
	}
	if (token.find("..") != std::string::npos)
		return (false);
	return (true);
}

void	parseIndex(std::vector<std::string>& tokens, size_t& i, std::vector<std::string>& dest, bool& index_set)
{
	if (index_set)
		throw (std::runtime_error("Cannot have two different index directives."));
	i++;
	index_set = true;
	dest.clear();
	while (i < tokens.size() && tokens[i] != ";" && !isDirective(tokens[i]))
	{
		if (!isValidIndexFile(tokens[i]))
			throw (std::runtime_error("Invalid index filename"));
		dest.push_back(tokens[i]);
		i++;
	}
	if (dest.empty())
		throw (std::runtime_error("Index directives requires at least one filename."));
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ';' after index directive"));
	i++;
}