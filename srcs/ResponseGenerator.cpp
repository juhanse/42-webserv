#include "ResponseGenerator.hpp"

ResponseGenerator::ResponseGenerator() {}
ResponseGenerator::~ResponseGenerator() {}

Location ResponseGenerator::_matchLocation(const std::string& requestPath, const ServerConfig& config) {
    int bestMatchIdx = -1;
    size_t longestPrefix = 0;

    for (size_t i = 0; i < config.locations.size(); ++i) {
        const std::string& locPath = config.locations[i].path;
        // Si le path de la requête commence par le path de la location
        if (requestPath.find(locPath) == 0) {
            // On garde celle qui a le préfixe le plus long (la plus précise)
            if (locPath.length() > longestPrefix) {
                longestPrefix = locPath.length();
                bestMatchIdx = i;
            }
        }
    }

    // Si aucune location ne match (ne devrait pas arriver si tu as une location /)
    if (bestMatchIdx == -1) {
        // Retourne une location par défaut ou gère l'erreur
    }
    return config.locations[bestMatchIdx];
}

HTTPResponse ResponseGenerator::generate(const HTTPRequest& req, const ServerConfig& config) {
    // 1. Trouver la Location
    Location loc = _matchLocation(req.getPath(), config);
    
    // 2. Vérifier la méthode
    bool allowed = false;
    for (size_t i = 0; i < loc.methods.size(); ++i) {
        if (loc.methods[i] == req.getMethod()) allowed = true;
    }
    if (!allowed) {
        HTTPResponse res;
        res.setStatusCode(405); // Method Not Allowed
        return res;
    }

    // 3. Détecter si c'est un CGI
    // if (!loc.cgi_ext.empty() && req.getPath().find(loc.cgi_ext) != std::string::npos) {
    //     return _handleCGI(req, loc);
    // }

    // 4. Sinon, traiter comme un fichier statique
    return _handleStatic(req, loc);
}

HTTPResponse ResponseGenerator::_handleStatic(const HTTPRequest& req, const Location& loc) {
    HTTPResponse res;
    
    // On construit le chemin réel : root + path
    // Exemple : ./www + /index.html
    std::string fullPath = loc.root + req.getPath();

    // Utilise la fonction stat() pour vérifier si le fichier existe
    struct stat buffer;
    if (stat(fullPath.c_str(), &buffer) != 0) {
        res.setStatusCode(404); // Not Found
        res.setBody("<html><body><h1>404 Not Found</h1></body></html>");
        return res;
    }

    // Si c'est un dossier, on devrait chercher l'index, mais restons simples pour l'instant
    if (S_ISDIR(buffer.st_mode)) {
        fullPath += "/" + loc.index;
    }

    std::string content = _readFile(fullPath);
    if (content.empty() && req.getPath() != "/") { // Erreur de lecture
        res.setStatusCode(403); // Forbidden
        return res;
    }

    res.setStatusCode(200);
    res.setBody(content);
    res.setHeader("Content-Type", _identifyContentType(fullPath));
    return res;
}

std::string ResponseGenerator::_identifyContentType(const std::string& path) {
    if (path.find(".html") != std::string::npos) return "text/html";
    if (path.find(".css") != std::string::npos) return "text/css";
    if (path.find(".png") != std::string::npos) return "image/png";
    if (path.find(".jpg") != std::string::npos) return "image/jpeg";
    if (path.find(".py") != std::string::npos) return "text/html"; // Le CGI renvoie du HTML
    return "text/plain";
}

std::string ResponseGenerator::_readFile(const std::string& path) {
    // On ouvre en mode binaire pour éviter les conversions de fin de ligne
    // (Crucial pour les images ou les fichiers sous différents OS)
    std::ifstream file(path.c_str(), std::ios::in | std::ios::binary);
    
    // Vérification de l'ouverture
    if (!file.is_open()) {
        return "";
    }

    // On utilise un stringstream pour lire tout le contenu du fichier d'un coup
    std::stringstream buffer;
    buffer << file.rdbuf();
    
    file.close();
    return buffer.str();
}
