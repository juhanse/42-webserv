/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseBodySize.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:52:42 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/30 16:32:07 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEBODYSIZE_HPP
# define PARSEBODYSIZE_HPP

#include "ConfigParser.hpp"

void	parseBodySize(std::vector<std::string>& tokens, size_t& i, Server& serv);

#endif