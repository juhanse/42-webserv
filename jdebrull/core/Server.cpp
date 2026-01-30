/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:43:31 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/30 18:29:36 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Server.hpp>

Server::Server() : 	host("localhost"), //default constructor
				port(80),
				server_name(),
				root(""),
				index(),
				client_max_body_size(1048576),
				error_page("") {
	}