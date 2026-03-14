#include "SessionManager.hpp"

SessionManager::SessionManager() {}
SessionManager::~SessionManager() {}

SessionManager& SessionManager::getInstance() {
	static SessionManager instance;
	return instance;
}

std::string SessionManager::_generateSessionID() {
	std::stringstream ss;
	srand(time(NULL));
	for (int i = 0; i < 16; ++i) {
		ss << std::hex << (rand() % 16);
	}
	return ss.str();
}

std::string SessionManager::createSession(const std::string& username, int ttl_seconds) {
	std::string id = _generateSessionID();
	SessionData data;
	data.username = username;
	data.expires_at = time(NULL) + ttl_seconds;
	_sessions[id] = data;
	return id;
}

bool SessionManager::isValidSession(const std::string& session_id) {
	std::map<std::string, SessionData>::iterator it = _sessions.find(session_id);
	if (it != _sessions.end()) {
		if (time(NULL) > it->second.expires_at) {
			_sessions.erase(it);
			return false;
		}
		return true;
	}
	return false;
}

SessionData SessionManager::getSession(const std::string& session_id) {
	return _sessions[session_id];
}

void SessionManager::cleanup() {
	std::map<std::string, SessionData>::iterator it = _sessions.begin();
	while (it != _sessions.end()) {
		if (time(NULL) > it->second.expires_at) {
			_sessions.erase(it++);
		} else {
			++it;
		}
	}
}
