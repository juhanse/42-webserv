/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:52:54 by jdebrull          #+#    #+#             */
/*   Updated: 2026/02/05 16:45:12 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

Location::Location() :
					client_max_size(1048576),
					path(""),
					root(""),
					upload(""),
					return_url(""),
					return_code(0),
					autoindex(false),
					autoindex_set(false),
					index(),
					index_set(),
					methods() {}