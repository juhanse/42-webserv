/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseLocation.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:49:34 by jdebrull          #+#    #+#             */
/*   Updated: 2026/03/18 13:49:34 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSELOCATION_HPP
# define PARSELOCATION_HPP

#include "ConfigParser.hpp"

void	parseLocation(std::vector<std::string>& tokens, size_t& i, ServerConfig&  serv);

#endif