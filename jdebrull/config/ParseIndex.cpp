/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseIndex.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:09:08 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/31 14:38:43 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseIndex.hpp"

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

void	parseIndex(std::vector<std::string>& tokens, size_t& i, std::vector<std::string>& dest)
{
	i++;
	if (!dest.empty())
		throw (std::runtime_error("Cannot have two different index directives."));
	bool found = false;
	while (i < tokens.size() && tokens[i] != ";")
	{
		if (!isValidIndexFile(tokens[i]))
			throw (std::runtime_error("Invalid index filename"));
		dest.push_back(tokens[i]);
		found = true;
		i++;
	}
	if (!found)
		throw (std::runtime_error("Index directives requires at least one filename."));
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ';' after index directive"));
	i++;
}