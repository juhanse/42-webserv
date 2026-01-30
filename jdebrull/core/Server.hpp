/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:39:59 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/30 18:30:07 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <string>
#include <vector>
#include <map>
#include "Location.hpp"

struct Server {
	std::string 			host;
	int						port;
	
	std::vector<std::string>	server_name;

	std::string					root;
	std::vector<std::string>	index;

	size_t						client_max_body_size;
	std::map<int, std::string>	error_page;
	
	std::vector<Location>	locations;
};

#endif