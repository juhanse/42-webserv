/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseIndex.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:49:18 by jdebrull          #+#    #+#             */
/*   Updated: 2026/03/18 13:49:18 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEINDEX_HPP
# define PARSEINDEX_HPP

#include "ConfigParser.hpp"

bool	isDirective(const std::string& token);
bool	isValidIndexFile(const std::string& token);

template <typename T>
void	parseIndex(std::vector<std::string>& tokens, size_t& i, T& config, bool& index_set)
{
	if (index_set)
		throw (std::runtime_error("Cannot have two different index directives."));

	i++;
	if (i >= tokens.size())
		throw (std::runtime_error("Missing value after index directive."));
	bool found = false;
	while (i < tokens.size() && tokens[i] != ";" && !isDirective(tokens[i]))
	{
		if (!isValidIndexFile(tokens[i]))
			throw (std::runtime_error("Invalid index filename"));
		config.addIndex(tokens[i]);
		found = true;
		i++;
	}
	if (!found)
		throw (std::runtime_error("Index directive requires at least one filename."));
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ';' after index directive"));
	i++;
	index_set = true;
}

#endif  