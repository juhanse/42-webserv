/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseListen.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:26:09 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/28 14:27:29 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSELISTEN_HPP
# define PARSELISTEN_HPP

#include "ConfigParser.hpp"

bool	parseListen(std::string tokens, Server& serv);

#endif