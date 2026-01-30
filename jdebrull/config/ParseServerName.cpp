/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseServerName.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 13:32:28 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/29 15:41:18 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseServerName.hpp"

static bool	isValidServerName(const std::string& token)
{
	if (token.empty())
		return (false);

	for (size_t i = 0; i < token.size(); ++i)
	{
		char c = token[i];
		if (!isAlNum(c) && c != '.' && c != '-')
			return false;
	}
	return true;
}

void	parseServerName(std::vector<std::string>& tokens, size_t& i, Server& serv)
{
	i++;
	if (i >= tokens.size())
		throw std::runtime_error("Expected server name after server_name");

	while (i < tokens.size() && tokens[i] != ";") 
	{
		if (!isValidServerName(tokens[i]))
			throw (std::runtime_error("Invalid character in the server_name directive."));
		serv.server_name.push_back(tokens[i]);
		i++;
	}
	
	if (i >= tokens.size())
		throw (std::runtime_error("Missing ';' after server_name directives."));
	if (serv.server_name.empty())
		throw (std::runtime_error("No server names provided."));
	i++;
}