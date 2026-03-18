/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugPrint.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:50:09 by jdebrull          #+#    #+#             */
/*   Updated: 2026/03/18 13:50:09 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUGPRINT_HPP
# define DEBUGPRINT_HPP

# include <iostream>
# include "../config/ServerConfig.hpp"

void printServers(const std::vector<ServerConfig>& servers);

#endif