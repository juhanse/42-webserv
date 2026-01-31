/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:50:30 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/31 17:43:49 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

#include <string>
#include <set>
#include <vector>

struct Location
{
	size_t						client_max_size;

	std::string					path;
	std::string					root;
	std::vector<std::string>	index;
	bool						autoindex;
	bool						autoindex_set;

	std::set<std::string> 		allowed_methods;
	Location();
};

#endif