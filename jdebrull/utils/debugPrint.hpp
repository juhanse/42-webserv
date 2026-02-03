/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugPrint.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:13:11 by jdebrull          #+#    #+#             */
/*   Updated: 2026/02/03 13:16:40 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUGPRINT_HPP
# define DEBUGPRINT_HPP

# include <iostream>
# include "../config/ConfigParser.hpp"

void printServers(const std::vector<Server> &servers);

#endif