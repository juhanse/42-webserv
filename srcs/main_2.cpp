#include "Webserver.hpp"
#include "ServerConfig.hpp"

int main(int ac, char **av) {
	// if (ac != 2) {
	// 	std::cerr << "Bad arguments: [./webserv [configuration file]]" << std::endl;
	// 	return (1);
	// }

	// std::cout << av[1] << std::endl;

	ServerConfig	testing = {8080, 50}; //use new to store in other objects
	std::vector<ServerConfig*> configs;
	configs.push_back(&testing);

	Webserver	webserv(configs);

	//handle signals?

	for (size_t i = 0; i < configs.size(); i++) {
		if (webserv.newServ(configs[i]) == -1) {
			std::cerr << "Servers couldn't init" << std::endl;
			//clean and free? in webserv destructor?
			return (1);
		}
	}
	webserv.runServ();
	//clean and free? in webserv destructor?
	return (0);
}
