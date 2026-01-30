/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRoot.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:17:54 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/30 18:42:50 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseRoot.hpp"

static bool isValidPath(const std::string& token)
{
	if (token.empty())
		return (false);
	if (token[0] != '/')
		return (false);
	for (size_t i = 0; i < token.size(); ++i)
	{
		char c = token[i];
		if (!isAlNum(c) && c != '/' && c != '_' && c != '-' && c != '.')
			return (false);
	}
	return (true);
}

void	parseRoot(const std::vector<std::string>& tokens, size_t& i, Server& serv)
{
	i++;
	if (i >= tokens.size())
		throw (std::runtime_error("Expected path after root"));
	if (!isValidPath(tokens[i]))
		throw (std::runtime_error("Invalid root path."));
	if (!serv.root.empty())
		throw (std::runtime_error("Only one path for root directive is allowed."));
	serv.root = tokens[i];
	i++;
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ';' after root directive."));
	i++;
}