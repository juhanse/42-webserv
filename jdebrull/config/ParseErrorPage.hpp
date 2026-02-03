/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseErrorPage.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:05:31 by jdebrull          #+#    #+#             */
/*   Updated: 2026/02/03 14:33:03 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEERRORPAGE_HPP
# define PARSEERRORPAGE_HPP

#include "ConfigParser.hpp"

void	parseErrorPage(std::vector<std::string>& tokens, size_t& i, Server& serv);
bool	isValidErrorCodePath(const std::string& token);

#endif