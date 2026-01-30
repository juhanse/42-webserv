/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseServerName.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 13:31:16 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/29 13:35:19 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSESERVERNAME_HPP
# define PARSESERVERNAME_HPP

#include "ConfigParser.hpp"

void	parseServerName(std::vector<std::string>& tokens, size_t& i, Server& serv);

#endif