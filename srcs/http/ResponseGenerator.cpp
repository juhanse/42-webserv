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

std::string ResponseGenerator::_getScriptDirectory(const std::string& scriptPath) {
    size_t pos = scriptPath.find_last_of('/');
    if (pos != std::string::npos) {
        return scriptPath.substr(0, pos);
    }
    return ".";
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
        return _handlePOST(req, loc, config);
    }
    else if (req.getMethod() == "DELETE") {
        return _handleDELETE(req, loc, config);
    }

    return _handleGET(req, loc, config);
}

HttpResponse ResponseGenerator::_handleGET(const HttpRequest& req, const LocationConfig& loc, const ServerConfig& config) {
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

HttpResponse ResponseGenerator::_handlePOST(const HttpRequest& req, const LocationConfig& loc, const ServerConfig& config) {
	std::string contentType = req.getHeader("Content-Type");

	if (contentType.find("multipart/form-data") != std::string::npos) {
		size_t pos = contentType.find("boundary=");
		if (pos != std::string::npos) {
			std::string boundary = contentType.substr(pos + 9);
			return _handleUpload(req, loc, config, boundary);
		}
	}

	HttpResponse res;
	res.setStatusCode(200);
	res.setBody("<html><body><h1>200 OK</h1><p>Formulaire classique recu avec succes.</p></body></html>");
	res.setHeader("Content-Type", "text/html");
	return res;
}

HttpResponse ResponseGenerator::_handleUpload(const HttpRequest& req, const LocationConfig& loc, const ServerConfig& config, const std::string& boundary) {
	HttpResponse res;
    std::string body = req.getBody();
    std::string searchBoundary = "--" + boundary;

    std::cout << "--- DEBUG UPLOAD ---" << std::endl;
    std::cout << "Boundary recu : [" << searchBoundary << "]" << std::endl;

    size_t fnPos = body.find("filename=\"");
    if (fnPos == std::string::npos) {
        std::cout << "ECHEC 1 : filename= non trouve dans le body." << std::endl;
        res.generateErrorPage(400, config);
        return res;
    }

    size_t fnStart = fnPos + 10;
    size_t fnEnd = body.find("\"", fnStart);
    if (fnEnd == std::string::npos) {
        std::cout << "ECHEC 2 : fin du nom de fichier non trouvee." << std::endl;
        res.generateErrorPage(400, config);
        return res;
    }

    std::string filename = body.substr(fnStart, fnEnd - fnStart);
    std::cout << "Fichier detecte : " << filename << std::endl;

    size_t dataStart = body.find("\r\n\r\n", fnEnd);
    if (dataStart == std::string::npos) {
        std::cout << "ECHEC 3 : separateur headers/body (\\r\\n\\r\\n) non trouve." << std::endl;
        res.generateErrorPage(400, config);
        return res;
    }
    dataStart += 4;

    size_t dataEnd = body.find("\r\n" + searchBoundary, dataStart);
    if (dataEnd == std::string::npos) {
        std::cout << "ECHEC 4 : fin du fichier / boundary de fin non trouve." << std::endl;
        res.generateErrorPage(400, config);
        return res;
    }

    std::cout << "Taille du fichier a ecrire : " << (dataEnd - dataStart) << " octets." << std::endl;

	std::string basePath = loc.getRoot() + req.getPath();
    if (!basePath.empty() && basePath[basePath.length() - 1] != '/') {
        basePath += "/";
    }
    std::string fullPath = basePath + filename;

	struct stat s;
	if (stat(fullPath.c_str(), &s) == 0 && S_ISDIR(s.st_mode)) {
		res.generateErrorPage(403, config);
		return res;
	}

	std::ofstream file(fullPath.c_str(), std::ios::out | std::ios::binary);
	if (!file.is_open()) {
		res.generateErrorPage(500, config);
		return res;
	}

	file.write(body.data() + dataStart, dataEnd - dataStart);
	file.close();

	res.setStatusCode(201);
	res.setBody("<html><body><h1>201 Created</h1><p>Fichier uploade avec succes !</p></body></html>");
	res.setHeader("Content-Type", "text/html");

	return res;
}

HttpResponse ResponseGenerator::_handleDELETE(const HttpRequest& req, const LocationConfig& loc, const ServerConfig& config) {
    HttpResponse res;
    std::string fullPath = loc.getRoot() + req.getPath();

    struct stat s;
    if (stat(fullPath.c_str(), &s) != 0) {
        res.generateErrorPage(404, config);
        return res;
    }

    if (S_ISDIR(s.st_mode)) {
        res.generateErrorPage(403, config);
        return res;
    }

    if (std::remove(fullPath.c_str()) == 0) {
        res.setStatusCode(204);
    } else {
        res.generateErrorPage(403, config);
    }

    return res;
}

HttpResponse ResponseGenerator::_handleCGI(const HttpRequest& req, const LocationConfig& loc, const ServerConfig& config) {
	HttpResponse res;
	std::string scriptPath = loc.getRoot() + req.getPath();

	struct stat s;
	if (stat(scriptPath.c_str(), &s) != 0) {
		res.generateErrorPage(404, config);
		return res;
	}

	size_t dot = scriptPath.find_last_of('.');
	std::string ext = "";
	if (dot != std::string::npos) {
		ext = scriptPath.substr(dot);
	}

	std::string cgiExec = "";
	const std::map<std::string, std::string>& cgiExts = loc.getCgiExtensions();
	std::map<std::string, std::string>::const_iterator it = cgiExts.find(ext);
	
	if (it != cgiExts.end()) {
		cgiExec = it->second;
	} else {
		res.generateErrorPage(500, config);
		return res;
	}

	char** envp = _createCGIEnv(req, loc, scriptPath);

	int pipe_in[2];
	int pipe_out[2];

	if (pipe(pipe_in) == -1 || pipe(pipe_out) == -1) {
		_freeEnv(envp);
		res.generateErrorPage(500, config);
		return res;
	}

	pid_t pid = fork();

	if (pid == -1) {
		_freeEnv(envp);
		close(pipe_in[0]); close(pipe_in[1]);
		close(pipe_out[0]); close(pipe_out[1]);
		res.generateErrorPage(500, config);
		return res;
	}

	if (pid == 0) {
		dup2(pipe_in[0], STDIN_FILENO);
		dup2(pipe_out[1], STDOUT_FILENO);

		close(pipe_in[0]); close(pipe_in[1]);
		close(pipe_out[0]); close(pipe_out[1]);

		std::string scriptDir = _getScriptDirectory(scriptPath);
		if (chdir(scriptDir.c_str()) == -1) {
			_freeEnv(envp);
			_exit(1);
		}

		std::string scriptName = scriptPath;
		size_t pos = scriptPath.find_last_of('/');
		if (pos != std::string::npos) {
			scriptName = scriptPath.substr(pos + 1);
		}

		char* args[3];
		args[0] = const_cast<char*>(cgiExec.c_str());
		args[1] = const_cast<char*>(scriptName.c_str());
		args[2] = NULL;

		execve(args[0], args, envp);
		
		_freeEnv(envp);
		_exit(1);
	}
	else {
		close(pipe_in[0]);
		close(pipe_out[1]);

		fcntl(pipe_in[1], F_SETFL, O_NONBLOCK);
		fcntl(pipe_out[0], F_SETFL, O_NONBLOCK);

		_freeEnv(envp);

		res.setStatusCode(100);
		res.setCgiPid(pid);
		res.setCgiFdIn(pipe_in[1]);
		res.setCgiFdOut(pipe_out[0]);
		
		return res;
	}
}
