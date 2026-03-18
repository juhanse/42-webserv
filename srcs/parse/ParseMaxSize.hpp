/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseMaxSize.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:49:40 by jdebrull          #+#    #+#             */
/*   Updated: 2026/03/18 13:49:40 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEMAXSIZE_HPP
# define PARSEMAXSIZE_HPP

#include "ConfigParser.hpp"

int	stringToInt(const std::string& token, size_t max);

template <typename T>
void	parseMaxSize(std::vector<std::string>& tokens, size_t& i, T& config, size_t max)
{
	i++;
	if (i >= tokens.size())
		throw (std::runtime_error("Missing directive of Client max body size."));
	
	int n = stringToInt(tokens[i], max);
	if (n == 0)
		throw (std::runtime_error("Max body size cannot be 0."));
	config.setClientMaxBodySize(n);
	
	i++;
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ';' at the end of directive."));
	i++;
}

#endif