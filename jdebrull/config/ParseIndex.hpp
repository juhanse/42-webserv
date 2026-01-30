/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseIndex.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:08:53 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/29 16:10:41 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEINDEX_HPP
# define PARSEINDEX_HPP

#include "ConfigParser.hpp"

void	parseIndex(std::vector<std::string>& tokens, size_t& i, Server& serv);

#endif