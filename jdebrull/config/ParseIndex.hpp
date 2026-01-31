/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseIndex.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:08:53 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/31 14:58:21 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEINDEX_HPP
# define PARSEINDEX_HPP

#include "ConfigParser.hpp"

void	parseIndex(std::vector<std::string>& tokens, size_t& i, std::vector<std::string>& dest);

#endif