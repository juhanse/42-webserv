#include "ServerConfig.hpp"
#include "Webserver.hpp"
#include "ResponseGenerator.hpp"


int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Usage: ./webserv [configuration file]" << std::endl;
		return (1);
	}

	std::cout << av[1] << std::endl;

	ServerConfig config;
	config.root = "./srcs/www";
	config.port = 8080;
	config.client_max_body_size = 50;

	Location locRoot;
	locRoot.path = "/";
	locRoot.root = "./srcs/www";
	locRoot.methods.push_back("GET");
	locRoot.index = "index.html";
	config.locations.push_back(locRoot);

    Location locTraitement;
    locTraitement.path = "/traitement";
    locTraitement.root = "./srcs/www/uploads";
    locTraitement.methods.push_back("POST");
    config.locations.push_back(locTraitement);

	Location locCgi;
	locCgi.path = "/cgi-bin";
	locCgi.root = "./srcs/www/cgi-bin";
	locCgi.methods.push_back("GET");
	locCgi.methods.push_back("POST");
	locCgi.cgi_ext = ".py";
	locCgi.cgi_uri = "/usr/bin/python3";
	config.locations.push_back(locCgi);

	std::vector<ServerConfig*> configurations;
	configurations.push_back(&config);

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
