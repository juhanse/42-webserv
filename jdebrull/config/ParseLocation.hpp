/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseLocation.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 12:37:53 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/31 12:39:33 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSELOCATION_HPP
# define PARSELOCATION_HPP

#include "ConfigParser.hpp"

void	parseLocation(std::vector<std::string>& tokens, size_t& i, Server&  serv);

#endif