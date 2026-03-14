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
