#pragma once

#include <iostream>
#include <vector>
#include <map>

struct Location {
    std::string              path;
    std::string              root;
    std::vector<std::string> methods;
    std::string              index;
    bool                     autoindex;
    std::string              cgi_uri;
    std::string              cgi_ext;
    std::string              upload_dir;
};

struct ServerConfig {
	//std::string 			host;
	int						port;
	// bool					listen_set;
	
	// std::vector<std::string>	server_name;

	std::string					root;
	// std::vector<std::string>	index;
	// bool						index_set;

	size_t						client_max_body_size;
	std::map<int, std::string>	error_pages;
	
	std::vector<Location>	locations;
	//ServerConfig(): port(8080), client_max_body_size(10) {};
};