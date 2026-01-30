/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestContext.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:44:45 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/12 17:48:51 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Location.hpp"

struct RequestContext {
	const Server*	server;
	const Location*	location;

	std::string	file_path;

	bool		autoindex;
	std::string	index;
	size_t		max_size;

	std::set<std::string>		allowed_methods;

	std::map<int, std::string>	error_pages;
};