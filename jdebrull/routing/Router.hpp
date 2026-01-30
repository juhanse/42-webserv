/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:57:01 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/12 18:02:18 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../core/RequestContext.hpp"
#include "../core/Server.hpp"
#include <vector>

class Router {
	public:
		Router(const std::vector<Server>& servers);
	
	private:
		const std::vector<Server>& servers_s;
	
		const Server&	matchLocation(const Server& server, const std::string& uri);
		std::string		resolvePath(const Server& server, const Location& location, const std::string& uri);
};