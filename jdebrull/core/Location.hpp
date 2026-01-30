/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:50:30 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/12 17:39:52 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <set>

struct Location {
	std::string	path;
	std::string	root;
	std::string	index;
	bool		autoindex;

	std::set<std::string> allowed_methods;

	size_t client_max_size;
};