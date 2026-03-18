/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseServerName.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:49:52 by jdebrull          #+#    #+#             */
/*   Updated: 2026/03/18 13:49:52 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSESERVERNAME_HPP
# define PARSESERVERNAME_HPP

#include "ConfigParser.hpp"

void	parseServerName(std::vector<std::string>& tokens, size_t& i, ServerConfig& serv);

#endif