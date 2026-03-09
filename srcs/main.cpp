#include "config/ServerConfig.hpp"
#include "Webserver.hpp"
#include "http/ResponseGenerator.hpp"
#include "parse/ConfigParser.hpp"

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Usage: ./webserv [configuration file]" << std::endl;
		return (1);
	}

	std::vector<ServerConfig> servers;
	std::vector<ServerConfig*> configurations;

	try
	{
		ConfigParser parser;

		servers = parser.parse(av[1]);
	
		std::cout << "No errors detected in parsing." << std::endl;
		printServers(servers);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Config error: " << e.what() << std::endl;
		return (1);
	}

	for (size_t i = 0; i < servers.size(); i++) {
		configurations.push_back(&servers[i]);
	}

	Webserver	webserv(configurations);

	for (size_t i = 0; i < configurations.size(); i++) {
		if (webserv.newServ(configurations[i]) == -1) {
			std::cerr << "Servers couldn't init" << std::endl;
			//clean and free? in webserv destructor?
			return (1);
		}
	}
	
	webserv.runServ();

	// ServerConfig config;
	// config.root = "./srcs/www";
	// config.port = 8080;
	// config.client_max_body_size = 50;

	// Location locRoot;
	// locRoot.path = "/";
	// locRoot.root = "./srcs/www";
	// locRoot.methods.push_back("GET");
	// locRoot.index = "index.html";
	// config.locations.push_back(locRoot);

    // Location locTraitement;
    // locTraitement.path = "/traitement";
    // locTraitement.root = "./srcs/www/uploads";
    // locTraitement.methods.push_back("POST");
    // config.locations.push_back(locTraitement);

	// Location locCgi;
	// locCgi.path = "/cgi-bin";
	// locCgi.root = "./srcs/www/cgi-bin";
	// locCgi.methods.push_back("GET");
	// locCgi.methods.push_back("POST");
	// locCgi.cgi_ext = ".py";
	// locCgi.cgi_path = "/usr/bin/python3";
	// config.locations.push_back(locCgi);

	// std::vector<ServerConfig*> configurations;
	// configurations.push_back(&config);

	//clean and free? in webserv destructor?

	return (0);
}
