#pragma once

#include <string>
#include <vector>
#include <map>
#include "LocationConfig.hpp"

class ServerConfig
{
	private:
		std::string					host;
		int							port;
		std::vector<std::string>	server_name;
		std::string					root;
		std::vector<std::string>	index;
		size_t						client_max_body_size;
		std::map<int, std::string>	error_page;
		std::vector<LocationConfig>		locations;
		

	public:
		ServerConfig();
		~ServerConfig();

		const std::string&					getHost() const;
		int									getPort() const;
		const std::vector<std::string>&		getServerNames() const;
		const std::string&					getRoot() const;
		size_t								getClientMaxBodysize() const;
		const std::vector<std::string>&		getIndex() const;
		const std::map<int, std::string>&	getErrorPages() const;
		const std::vector<LocationConfig>&	getLocations() const;
		
		void	setHost(const std::string& h);
		void	setPort(int p);
		void	setRoot(const std::string& r);
		void	setClientMaxBodySize(size_t max);
		
		void	addServerName(const std::string& name);
		void	addIndex(const std::string& file);
		void	addErrorPage(int code, const std::string& path);
		void	addLocation(const LocationConfig& loc);

};


class Config
{
	private:
		std::vector<ServerConfig> servers;
	
	public:
		void	addServer(const ServerConfig& s);
		const	std::vector<ServerConfig>& getServers() const;
};
