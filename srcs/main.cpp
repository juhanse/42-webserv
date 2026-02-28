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

	Location locCgi;
	locCgi.path = "/cgi-bin";
	locCgi.root = "./www/cgi-bin";
	locCgi.methods.push_back("GET");
	locCgi.methods.push_back("POST");
	locCgi.cgi_ext = ".py";
	locCgi.cgi_path = "/usr/bin/python3";
	config.locations.push_back(locCgi);

	// Request
	std::string raw = "GET /index.html HTTP/1.0\r\n"
					"Host: localhost\r\n"
					"\r\n";

	HTTPRequest req;
	req.parse(raw);

	std::cout << "--- Requête Reçue ---" << std::endl;
	std::cout << "Méthode : " << req.getMethod() << " | Path : " << req.getPath() << std::endl;

	ResponseGenerator generator;
	HTTPResponse res = generator.generate(req, config);

	std::cout << "\n--- Réponse Générée ---" << std::endl;
	std::cout << res.getRawResponse() << std::endl;

	return (0);
}
