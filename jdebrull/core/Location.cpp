/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 16:52:54 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/31 17:40:56 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

Location::Location() :
					client_max_size(1048576),
					path(""),
					root(""),
					index(),
					autoindex(false),
					autoindex_set(false),
					allowed_methods() {}