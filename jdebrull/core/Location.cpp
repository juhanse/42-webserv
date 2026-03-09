#include "Location.hpp"

LocationConfig::LocationConfig() : client_max_size(0), return_code(0), autoindex(false) {}

LocationConfig::~LocationConfig() {}

const std::string&	LocationConfig::getPath() const {
	return (path);
}

const std::string&	LocationConfig::getRoot() const {
	return (root);
}

const std::vector<std::string>&	LocationConfig::getIndex() const {
	return (index);
}

const std::set<std::string>&	LocationConfig::getMethods() const {
	return (methods);
}

size_t	LocationConfig::getClientMaxBodySize() const {
	return (client_max_size);
}

bool	LocationConfig::getAutoIndex() const {
	return (autoindex);
}

int		LocationConfig::getReturnCode() const {
	return (return_code);
}

const std::string&	LocationConfig::getReturnUrl() const {
	return (return_url);
}

const std::map<std::string, std::string>&	LocationConfig::getCgiExtensions() const {
	return (cgi_extension);
}

const std::string&	LocationConfig::getUploadPath() const {
	return (upload);
}

void	LocationConfig::setPath(const std::string& p) {
	path = p;
}

void	LocationConfig::setRoot(const std::string& r) {
	root = r;
}

void	LocationConfig::setClientMaxBodySize(size_t size) {
	client_max_size = size;
}

void	LocationConfig::setAutoIndex(bool	value) {
	autoindex = value;
}

void	LocationConfig::setReturn(int code, const std::string& url) {
	return_code = code;
	return_url = url;
}

void	LocationConfig::setUpload(const std::string& path) {
	upload = path;
}

void	LocationConfig::addIndex(const std::string& file) {
	index.push_back(file);
}

void	LocationConfig::addMethod(const std::string& method) {
	if (methods.count(method))
		throw (std::runtime_error("Duplicate method in allowed methods is not allowed."));
	
	methods.insert(method);
}

void	LocationConfig::addCgiExtension(const std::string& ext, const std::string& path) {
	if (cgi_extension.count(ext))
		throw (std::runtime_error("Duplicate cgi_extension directive for the same extension."));

	cgi_extension[ext] = path;
}