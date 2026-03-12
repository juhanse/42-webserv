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
		//printServers(servers);
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

	//clean and free? in webserv destructor?

	return (0);
}
