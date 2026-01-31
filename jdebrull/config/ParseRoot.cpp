/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRoot.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:17:54 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/31 15:55:56 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseRoot.hpp"

static bool isValidPath(const std::string& token)
{
	if (token.empty())
		return (false);
	if (token[0] != '/')
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

void	parseRoot(const std::vector<std::string>& tokens, size_t& i, std::string& dest)
{
	if (!dest.empty())
		throw (std::runtime_error("Duplicate root directive is not allowed in the same block."));
	i++;
	if (i >= tokens.size())
		throw (std::runtime_error("Expected path after root."));
	if (!isValidPath(tokens[i]))
		throw (std::runtime_error("Invalid root path."));
	dest = tokens[i];
	i++;
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ';' after root directive."));
	i++;
}
