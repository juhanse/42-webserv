/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseListen.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:49:24 by jdebrull          #+#    #+#             */
/*   Updated: 2026/03/18 13:49:24 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSELISTEN_HPP
# define PARSELISTEN_HPP

#include "ConfigParser.hpp"

void	parseListen(std::vector<std::string>& tokens, size_t& i, ServerConfig& serv, bool& listen_set);

#endif