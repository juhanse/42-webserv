/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseErrorPage.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:06:46 by jdebrull          #+#    #+#             */
/*   Updated: 2026/02/18 16:18:14 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseErrorPage.hpp"

bool isValidErrorCodePath(const std::string& token)
{
	if (token.empty())
		return (false);
	if (token[0] != '/' && token[0] != '.')
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

static int	isValidCode(const std::string& token)
{
	int	n = 0;
	for (size_t i = 0; i < token.size(); ++i)
	{
		char c = token[i];
		if (!isDigit(c))
			throw (std::runtime_error("Only numbers are allowed for the error_page code " + token));
		n = (n * 10) + (c -'0');
		if (n > 599)
			throw (std::runtime_error("Error page code is not in the right range [400,599]."));
	}
	if (n < 400)
		throw (std::runtime_error("Error page code is not in the right range [400,599]."));
	return (n);
}

void	parseErrorPage(std::vector<std::string>& tokens, size_t& i, Server& serv)
{
	i++;
	if (i >= tokens.size())
		throw (std::runtime_error("Missing error code for the error_page directive."));

	std::vector<int>	codes;
	while (i < tokens.size() && tokens[i] != ";")
	{
		if (tokens[i][0] == '/' || tokens[i][0] == '.')
			break ;

		int	code = isValidCode(tokens[i]);
		for (size_t j = 0; j < codes.size(); ++j)
		{
			if (codes[j] == code)
				throw (std::runtime_error("Duplicate error code for the error_page directive."));
		}
		codes.push_back(code);
		i++;
	}
	if (codes.empty())
		throw (std::runtime_error("Missing a valid code for the error_page directive."));
	
	if (i >= tokens.size() || !isValidErrorCodePath(tokens[i]))
		throw (std::runtime_error("Missing or invalid path for the error_page directive " + tokens[i]));

	std::string path = tokens[i];
	i++;
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ';' after error_page directive."));
	for (size_t j = 0; j < codes.size(); ++j)
		serv.error_page[codes[j]] = path;
	i++;
}