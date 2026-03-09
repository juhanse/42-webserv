#include "../core/RequestContext.hpp"
#include "../core/Server.hpp"
#include <vector>

class Router {
	public:
		Router(const std::vector<Server>& servers);
	
	private:
		const std::vector<Server>& servers_s;
	
		const Server&	matchLocation(const Server& server, const std::string& uri);
		std::string		resolvePath(const Server& server, const Location& location, const std::string& uri);
};