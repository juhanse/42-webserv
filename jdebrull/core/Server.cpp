/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:43:31 by jdebrull          #+#    #+#             */
/*   Updated: 2026/02/05 16:43:49 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server() : host(""),
					port(0),
					listen_set(false),
					server_name(),
					root(""),
					index(1, "index.html"),
					index_set(false),
					client_max_body_size(1048576),
					error_page(),
					locations() {}