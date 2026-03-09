#include "Server.hpp"
#include "Location.hpp"

struct RequestContext {
	const Server*	server;
	const Location*	location;

	std::string	file_path;

	bool		autoindex;
	std::string	index;
	size_t		max_size;

	std::set<std::string>		allowed_methods;

	std::map<int, std::string>	error_pages;
};