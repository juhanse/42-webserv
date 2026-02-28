#include "ResponseGenerator.hpp"

ResponseGenerator::ResponseGenerator() {}
ResponseGenerator::~ResponseGenerator() {}

const Location* ResponseGenerator::_matchLocation(const std::string& requestPath, const ServerConfig& config) {
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

	// SÉCURITÉ : Si aucune location ne correspond, on renvoie NULL
	if (bestMatchIdx == -1) {
		return NULL; 
	}

	// return de l'adresse de la location trouvée
	return &config.locations[bestMatchIdx];
}

HTTPResponse ResponseGenerator::generate(const HTTPRequest& req, const ServerConfig& config) {
	HTTPResponse res;

	// 1. Trouver la Location (On récupère un pointeur)
	const Location* locPtr = _matchLocation(req.getPath(), config);
	if (locPtr == NULL) {
		res.generateErrorPage(404, config);
		return res;
	}

	// On déréférence le pointeur pour une utilisation plus simple ensuite
	const Location& loc = *locPtr;

	// 2. Vérifier si la méthode est autorisée
	bool allowed = false;
	for (size_t i = 0; i < loc.methods.size(); ++i) {
		if (loc.methods[i] == req.getMethod()) {
			allowed = true;
			break;
		}
	}

	if (!allowed) {
		res.generateErrorPage(405, config);
		return res;
	}

	// 3. Détecter si c'est un CGI (commenté pour l'instant)
	// if (!loc.cgi_ext.empty() && req.getPath().find(loc.cgi_ext) != std::string::npos) {
	//     return _handleCGI(req, loc, config); // N'oublie pas de passer config ici aussi plus tard
	// }

	return _handleStatic(req, loc, config);
}

HTTPResponse ResponseGenerator::_handleStatic(const HTTPRequest& req, const Location& loc, const ServerConfig& config) {
	HTTPResponse res;
	std::string fullPath = loc.root + req.getPath();

	struct stat s;
	if (stat(fullPath.c_str(), &s) != 0) {
		res.generateErrorPage(404, config);
		return res;
	}

	if (S_ISDIR(s.st_mode)) {
		fullPath += "/" + loc.index;

		if (stat(fullPath.c_str(), &s) != 0) {
			res.generateErrorPage(404, config);
			return res;
		}
	}

	std::string content = _readFile(fullPath);
	if (content.empty()) {
		res.generateErrorPage(403, config);
		return res;
	}

	res.setStatusCode(200);
	res.setBody(content);
	res.setContentType(fullPath);
	
	return res;
}

std::string ResponseGenerator::_readFile(const std::string& path) {
	// Ouverture en mode binaire (pour images/fichiers compilés)
	std::ifstream file(path.c_str(), std::ios::in | std::ios::binary);
	if (!file) {
		return "";
	}

	// Lecture en bloc optimisée
	std::stringstream buffer;
	buffer << file.rdbuf();

	return buffer.str();
}
