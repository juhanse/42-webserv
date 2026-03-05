#include "Config.hpp"
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include "ResponseGenerator.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <map>

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Usage: ./webserv [configuration file]" << std::endl;
		return (1);
	}

	std::cout << av[1] << std::endl;

	ServerConfig config;
	config.root = "./srcs/www";

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
	locCgi.cgi_path = "/usr/bin/python3";
	config.locations.push_back(locCgi);

	// Mock request
    std::string rawGet = "GET / HTTP/1.0\r\n"
			"Host: localhost\r\n"
			"Content-Type: application/x-www-form-urlencoded\r\n"
			"Content-Length: 33\r\n";

	std::string rawPost = "POST /traitement HTTP/1.0\r\n"
			"Host: localhost\r\n"
			"Content-Type: application/x-www-form-urlencoded\r\n"
			"Content-Length: 33\r\n"
			"\r\n"
			"utilisateur=juhanse&message=Coucou";

    HTTPRequest req;
    req.parse(rawPost);

	std::cout << "--- Requête Reçue ---" << std::endl;
	std::cout << "Méthode : " << req.getMethod() << " | Path : " << req.getPath() << std::endl;

	ResponseGenerator generator;
	HTTPResponse res = generator.generate(req, config);

	std::cout << "\n--- Réponse Générée ---" << std::endl;
	std::cout << res.getRawResponse() << std::endl;

	return (0);
}
