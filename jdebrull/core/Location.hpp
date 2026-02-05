/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:50:30 by jdebrull          #+#    #+#             */
/*   Updated: 2026/02/05 16:45:00 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <string>
# include <set>
# include <map>
# include <vector>

struct Location
{
	size_t						client_max_size;

	std::string					path;
	std::string					root;
	std::string					upload;
	std::string					return_url;
	int							return_code;
	bool						autoindex;
	bool						autoindex_set;
	
	std::vector<std::string>			index;
	bool								index_set;
	std::set<std::string> 				methods;
	std::map<std::string, std::string>	cgi_extension;
	Location();
};

#endif