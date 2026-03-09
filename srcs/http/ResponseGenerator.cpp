#include "ResponseGenerator.hpp"

ResponseGenerator::ResponseGenerator() {}
ResponseGenerator::~ResponseGenerator() {}

const LocationConfig* ResponseGenerator::_matchLocation(const std::string& requestPath, const ServerConfig& config) {
	int bestMatchIdx = -1;
	size_t longestPrefix = 0;

	const std::vector<LocationConfig>& locations = config.getLocations();
	for (size_t i = 0; i < locations.size(); ++i) {
		const std::string& locPath = locations[i].getPath();
		
		// Si le path de la requête commence par le path de la location
		if (requestPath.find(locPath) == 0) {
			// On garde celle qui a le préfixe le plus long (la plus précise)
			if (locPath.length() > longestPrefix) {
				longestPrefix = locPath.length();
				bestMatchIdx = i;
			}
		}
	}

	if (bestMatchIdx == -1) {
		return NULL; 
	}

	// return de l'adresse de la location trouvée
	return &locations[bestMatchIdx];
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

char** ResponseGenerator::_createCGIEnv(const HttpRequest& req, const LocationConfig& loc, const std::string& scriptPath) {
	std::map<std::string, std::string> envMap;

	envMap["REQUEST_METHOD"] = req.getMethod();
	envMap["SCRIPT_FILENAME"] = scriptPath;
	envMap["SERVER_PROTOCOL"] = "HTTP/1.0";
	envMap["PATH_INFO"] = req.getPath();
	envMap["QUERY_STRING"] = req.getQuery();

	if (req.getMethod() == "POST") {
		std::stringstream ss;
		ss << req.getContentLength();
		envMap["CONTENT_LENGTH"] = ss.str();
		envMap["CONTENT_TYPE"] = req.getHeader("Content-Type");
	}

	char** envp = new char*[envMap.size() + 1];
	int i = 0;

	for (std::map<std::string, std::string>::iterator it = envMap.begin(); it != envMap.end(); ++it) {
		std::string envStr = it->first + "=" + it->second;

		envp[i] = new char[envStr.length() + 1];
		std::strcpy(envp[i], envStr.c_str());
		i++;
	}
	envp[i] = NULL;

	return envp;
}

void ResponseGenerator::_freeEnv(char** envp) {
	if (!envp) return;

	for (int i = 0; envp[i] != NULL; ++i) {
		delete[] envp[i];
	}

	delete[] envp;
}

HttpResponse ResponseGenerator::generate(const HttpRequest& req, const ServerConfig& config) {
    HttpResponse res;

    // 1. Trouver la Location
    const LocationConfig* locPtr = _matchLocation(req.getPath(), config);
    if (locPtr == NULL) {
        res.generateErrorPage(404, config);
        return res;
    }
    const LocationConfig& loc = *locPtr;

    // 2. Check autorisations
    bool allowed = false;
    const std::set<std::string>& methods = loc.getMethods();
	if (methods.find(req.getMethod()) != methods.end()) {
		allowed = true;
	}
    if (!allowed) {
        res.generateErrorPage(405, config);
        return res;
    }

    // 3. L'aiguillage
	const std::map<std::string, std::string>& cgi = loc.getCgiExtensions();

	size_t dot = req.getPath().rfind('.');
	bool isCGI = false;

	if (dot != std::string::npos) {
		std::string ext = req.getPath().substr(dot);
		isCGI = (cgi.find(ext) != cgi.end());
	}

    if (isCGI) {
        return _handleCGI(req, loc, config);
    }

    if (req.getMethod() == "POST") {
        return _handlePostUpload(req, loc, config);
    }
    else if (req.getMethod() == "DELETE") {
        return _handleDelete(req, loc, config);
    }

    return _handleStatic(req, loc, config);
}

HttpResponse ResponseGenerator::_handleStatic(const HttpRequest& req, const LocationConfig& loc, const ServerConfig& config) {
	HttpResponse res;
	std::string fullPath = loc.getRoot() + req.getPath();

	struct stat s;
	if (stat(fullPath.c_str(), &s) != 0) {
		res.generateErrorPage(404, config);
		return res;
	}

	if (S_ISDIR(s.st_mode)) {
		const std::vector<std::string>& indexes = loc.getIndex();
		bool found = false;

		for (size_t i = 0; i < indexes.size(); ++i) {
			std::string candidate = fullPath + "/" + indexes[i];

			if (stat(candidate.c_str(), &s) == 0) {
				fullPath = candidate;
				found = true;
				break;
			}
		}

		if (!found) {
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

HttpResponse ResponseGenerator::_handleCGI(const HttpRequest& req, const LocationConfig& loc, const ServerConfig& config) {
	HttpResponse res;
	std::string scriptPath = loc.getRoot() + req.getPath();

	// Check si le script existe
	struct stat s;
	if (stat(scriptPath.c_str(), &s) != 0) {
		res.generateErrorPage(404, config);
		return res;
	}

	// char** envp = _createCGIEnv(req, loc, scriptPath);

	// // 3. Création des tuyaux (0 = lecture, 1 = écriture)
	// int pipe_in[2];  // Le serveur écrit dedans, Python lit
	// int pipe_out[2]; // Python écrit dedans, le serveur lit
	// if (pipe(pipe_in) == -1 || pipe(pipe_out) == -1) {
	// 	_freeEnv(envp);
	// 	res.generateErrorPage(500, config);
	// 	return res;
	// }

	// // 4. Clonage (Fork)
	// pid_t pid = fork();
	// if (pid == -1) {
	// 	_freeEnv(envp);
	// 	close(pipe_in[0]); close(pipe_in[1]);
	// 	close(pipe_out[0]); close(pipe_out[1]);
	// 	res.generateErrorPage(500, config);
	// 	return res;
	// }
	// // --- PROCESSUS ENFANT (PYTHON) ---
	// if (pid == 0) {
	// 	// Redirection des entrées/sorties standards
	// 	dup2(pipe_in[0], STDIN_FILENO);
	// 	dup2(pipe_out[1], STDOUT_FILENO);
	// 	// Fermeture des descripteurs inutiles pour l'enfant
	// 	close(pipe_in[0]); close(pipe_in[1]);
	// 	close(pipe_out[0]); close(pipe_out[1]);

	// 	char* args[3];
	// 	args[0] = const_cast<char*>(loc.cgi_path.c_str());
	// 	args[1] = const_cast<char*>(scriptPath.c_str());
	// 	args[2] = NULL;

	// 	execve(args[0], args, envp);
	// 	// Si execve échoue
	// 	_exit(1);
	// } 
	// // --- PROCESSUS PARENT (SERVEUR C++) ---
	// else {	
	// 	// Fermeture des côtés des tuyaux que le parent n'utilise pas
	// 	close(pipe_in[0]);
	// 	close(pipe_out[1]);

	// 	// PASSAGE EN NON-BLOQUANT (CRUCIAL POUR LE MULTI-CGI)
	// 	fcntl(pipe_in[1], F_SETFL, O_NONBLOCK);
	// 	fcntl(pipe_out[0], F_SETFL, O_NONBLOCK);

	// 	_freeEnv(envp);

	// 	// On configure une réponse temporaire pour passer le relais au Client
	// 	res.setStatusCode(100);

	// 	res.setCgiPid(pid);
	// 	res.setCgiFdIn(pipe_in[1]);
	// 	res.setCgiFdOut(pipe_out[0]);

	// 	return res;
	// }
}

HttpResponse ResponseGenerator::_handlePostUpload(const HttpRequest& req, const LocationConfig& loc, const ServerConfig& config) {
	HttpResponse res;
	std::string fullPath = loc.getRoot() + req.getPath();

	struct stat s;
	
	// Check si le chemin demandé est un dossier existant
	// Impossible d'écraser un dossier avec le body de la requête
	if (stat(fullPath.c_str(), &s) == 0 && S_ISDIR(s.st_mode)) {
		res.generateErrorPage(403, config);
		return res;
	}

	// Création ou écrasement du fichier en mode binaire
	std::ofstream file(fullPath.c_str(), std::ios::out | std::ios::binary);
	
	// Si l'ouverture échoue
	if (!file.is_open()) {
		res.generateErrorPage(500, config);
		return res;
	}

	file << req.getBody();
	// Le RAII fermera le fichier automatiquement à la fin du bloc, 
	// mais on peut le faire explicitement par clarté.
	file.close();

	// Réponse
	res.setStatusCode(201);

	std::string html = "<html><body><h1>201 Created</h1><p>Fichier uploade avec succes !</p></body></html>";
	res.setBody(html);
	res.setHeader("Content-Type", "text/html");

	return res;
}

HttpResponse ResponseGenerator::_handleDelete(const HttpRequest& req, const LocationConfig& loc, const ServerConfig& config) {
    HttpResponse res;
    std::string fullPath = loc.getRoot() + req.getPath();

    struct stat s;
    
    // Check si le fichier existe
    if (stat(fullPath.c_str(), &s) != 0) {
        res.generateErrorPage(404, config);
        return res;
    }

    // Check si c'est un dossier
    if (S_ISDIR(s.st_mode)) {
        res.generateErrorPage(403, config);
        return res;
    }

    if (std::remove(fullPath.c_str()) == 0) {
        res.setStatusCode(204); // "No Content" -> Code standard pour un DELETE réussi et pas besoin de body
    } else {
        res.generateErrorPage(403, config);
    }

    return res;
}
