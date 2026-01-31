/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseMaxSize.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:52:42 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/31 15:30:07 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEMAXSIZE_HPP
# define PARSEMAXSIZE_HPP

#include "ConfigParser.hpp"

void	parseMaxSize(std::vector<std::string>& tokens, size_t& i, size_t& dest, size_t max);

#endif