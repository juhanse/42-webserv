/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SessionManager.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:59:11 by juhanse           #+#    #+#             */
/*   Updated: 2026/03/18 13:59:11 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include <ctime>
#include <cstdlib>
#include <sstream>

struct SessionData {
	std::string	username;
	time_t		expires_at;
};

class SessionManager {
	private:
		std::map<std::string, SessionData>	_sessions;
		std::string							_generateSessionID();

	public:
		SessionManager();
		~SessionManager();

		std::string				createSession(const std::string& username, int ttl_seconds);
		static SessionManager&	getInstance();
		SessionData				getSession(const std::string& session_id);
		bool					isValidSession(const std::string& session_id);
		void					cleanup();
};
