/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseListen.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:26:09 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/31 16:11:23 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSELISTEN_HPP
# define PARSELISTEN_HPP

#include "ConfigParser.hpp"

void	parseListen(std::vector<std::string>& tokens, size_t& i, Server& serv);

#endif