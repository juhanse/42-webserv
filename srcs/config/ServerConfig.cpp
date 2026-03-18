/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:48:55 by jdebrull          #+#    #+#             */
/*   Updated: 2026/03/18 13:48:55 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConfig.hpp"

ServerConfig::ServerConfig() : port(0), client_max_body_size(1048576) {}

ServerConfig::~ServerConfig() {}

const std::string&	ServerConfig::getHost() const {
	return (host);
}

int	ServerConfig::getPort() const {
	return (port);
}

const std::string&	ServerConfig::getRoot() const {
	return (root);
}

size_t	ServerConfig::getClientMaxBodysize() const {
	return (client_max_body_size);
}

const std::vector<std::string>& ServerConfig::getServerNames() const {
	return (server_name);
}

const std::vector<std::string>& ServerConfig::getIndex() const {
	return (index);
}

const std::map<int, std::string>& ServerConfig::getErrorPages() const {
	return (error_page);
}

const std::vector<LocationConfig>& ServerConfig::getLocations() const {
	return (locations);
}

void	ServerConfig::setHost(const std::string& h) {
	host = h;
}
void	ServerConfig::setPort(int p) {
	port = p;
}

void	ServerConfig::setRoot(const std::string& r) {
	root = r;
}

void	ServerConfig::setClientMaxBodySize(size_t max) {
	client_max_body_size = max;
}

void	ServerConfig::addServerName(const std::string& name) {
	server_name.push_back(name);
}

void	ServerConfig::addIndex(const std::string& file) {
	index.push_back(file);
}

void	ServerConfig::addErrorPage(int code, const std::string& path) {
	error_page[code] = path;
}

void	ServerConfig::addLocation(const LocationConfig& loc) {
	locations.push_back(loc);
}

void	Config::addServer(const ServerConfig& s) {
	servers.push_back(s);
}

const std::vector<ServerConfig>& Config::getServers() const {
	return (servers);
}