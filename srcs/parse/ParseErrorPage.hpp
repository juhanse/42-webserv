/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseErrorPage.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:49:13 by jdebrull          #+#    #+#             */
/*   Updated: 2026/03/18 13:49:13 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEERRORPAGE_HPP
# define PARSEERRORPAGE_HPP

#include "ConfigParser.hpp"

void	parseErrorPage(std::vector<std::string>& tokens, size_t& i, ServerConfig& serv);
bool	isValidErrorCodePath(const std::string& token);

#endif