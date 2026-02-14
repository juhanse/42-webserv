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
    
    // 1. MOCK CONFIGURATION
    ServerConfig config;
    config.root = "./www";

    // Configuration de la route "/"
    Location locRoot;
    locRoot.path = "/";
    locRoot.root = "./www";
    locRoot.methods.push_back("GET");
    locRoot.index = "index.html";
    config.locations.push_back(locRoot);

    // Configuration de la route "/cgi-bin"
    Location locCgi;
    locCgi.path = "/cgi-bin";
    locCgi.root = "./www/cgi-bin";
    locCgi.methods.push_back("GET");
    locCgi.methods.push_back("POST");
    locCgi.cgi_ext = ".py";
    locCgi.cgi_path = "/usr/bin/python3";
    config.locations.push_back(locCgi);

    // 2. MOCK REQUEST
    // Teste ici différentes URLs : "/index.html", "/inexistant.html", "/cgi-bin/test.py"
    std::string raw = "GET /index.html HTTP/1.1\r\n"
                      "Host: localhost\r\n"
                      "\r\n";

    HTTPRequest req;
    req.parse(raw);

    std::cout << "--- Requête Reçue ---" << std::endl;
    std::cout << "Méthode : " << req.getMethod() << " | Path : " << req.getPath() << std::endl;

    // 3. GÉNÉRATION DE LA RÉPONSE (MOI)
    ResponseGenerator generator;
    HTTPResponse res = generator.generate(req, config);

    // 4. AFFICHAGE DU RÉSULTAT
    std::cout << "\n--- Réponse Générée ---" << std::endl;
    // On affiche le début de la réponse pour vérifier le status code et les headers
    std::cout << res.getRawResponse() << std::endl;

    return (0);
}
