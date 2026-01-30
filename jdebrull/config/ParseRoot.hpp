/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRoot.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:16:42 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/29 15:22:52 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEROOT_HPP
# define PARSEROOT_HPP

#include "ConfigParser.hpp"

void	parseRoot(const std::vector<std::string>& tokens, size_t& i, Server& serv);

#endif