/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseBodySize.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:51:52 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/30 16:37:13 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseBodySize.hpp"

static int	stringToInt(const std::string& token)
{
	if (token.empty())
		throw (std::runtime_error("Empty number"));	
	
	long	n = 0;

	for (size_t i = 0; i < token.size(); ++i)
	{
		char c = token[i];
		if (!isDigit(c))
			throw (std::runtime_error("Invalid number: " + token));
		n = n * 10 + c - '0';
		if (n > 1048576)
			throw (std::runtime_error("Number: " + token + " is to big 1MB is the clients max body size"));
	}
	return (static_cast<int>(n));
}

void	parseBodySize(std::vector<std::string>& tokens, size_t& i, Server& serv)
{
	i++;
	if (i >= tokens.size())
		throw (std::runtime_error("Missing directive of Client max body size."));
	
	int n = stringToInt(tokens[i]);
	if (n == 0)
		throw (std::runtime_error("Max body size cannot be 0."));
	serv.client_max_body_size = n;
	
	i++;
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ';' at the end of directive."));
	i++;
}
