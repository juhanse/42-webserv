/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRoot.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:16:42 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/31 14:49:29 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEROOT_HPP
# define PARSEROOT_HPP

#include "ConfigParser.hpp"

void	parseRoot(const std::vector<std::string>& tokens, size_t& i, std::string& dest);

#endif