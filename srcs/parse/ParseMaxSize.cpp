/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseMaxSize.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:49:36 by jdebrull          #+#    #+#             */
/*   Updated: 2026/03/18 13:49:37 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseMaxSize.hpp"

int	stringToInt(const std::string& token, size_t max)
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
		if (n > (int)max)
			throw (std::runtime_error("Number: " + token + " is to big."));
	}
	return (static_cast<int>(n));
}
