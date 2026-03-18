/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseIndex.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:49:15 by jdebrull          #+#    #+#             */
/*   Updated: 2026/03/18 13:49:16 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseIndex.hpp"

bool	isDirective(const std::string& token)
{
	return ( token == "methods" || token == "root" || token == "index"
			|| token == "autoindex" || token == "client_max_size"
			|| token == "upload" || token == "return" || token == "cgi_extension");
}

bool	isValidIndexFile(const std::string& token)
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