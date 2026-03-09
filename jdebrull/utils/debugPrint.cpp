#include "debugPrint.hpp"

#include "debugPrint.hpp"

static void printLocation(const LocationConfig& loc)
{
    std::cout << "    Location:" << std::endl;
    std::cout << "      path: " << loc.getPath() << std::endl;

    if (!loc.getRoot().empty())
        std::cout << "      root: " << loc.getRoot() << std::endl;

    if (!loc.getIndex().empty())
    {
        std::cout << "      index:";
        const std::vector<std::string>& index = loc.getIndex();
        for (size_t i = 0; i < index.size(); ++i)
            std::cout << " " << index[i];
        std::cout << std::endl;
    }

    std::cout << "      autoindex: "
              << (loc.getAutoIndex() ? "on" : "off")
              << std::endl;

    if (!loc.getMethods().empty())
    {
        std::cout << "      allowed_methods:";
        const std::set<std::string>& methods = loc.getMethods();
        for (std::set<std::string>::const_iterator it = methods.begin();
             it != methods.end(); ++it)
            std::cout << " " << *it;
        std::cout << std::endl;
    }

    if (loc.getClientMaxBodySize() > 0)
        std::cout << "      client_max_body_size: "
                  << loc.getClientMaxBodySize()
                  << std::endl;

    if (loc.getReturnCode() != 0)
    {
        std::cout << "      return: "
                  << loc.getReturnCode();
        if (!loc.getReturnUrl().empty())
            std::cout << " " << loc.getReturnUrl();
        std::cout << std::endl;
    }

    if (!loc.getUploadPath().empty())
        std::cout << "      upload: "
                  << loc.getUploadPath()
                  << std::endl;

    if (!loc.getCgiExtensions().empty())
    {
        std::cout << "      cgi_extension:" << std::endl;
        const std::map<std::string, std::string>& cgi = loc.getCgiExtensions();
        for (std::map<std::string, std::string>::const_iterator it = cgi.begin();
             it != cgi.end(); ++it)
            std::cout << "        "
                      << it->first << " -> "
                      << it->second << std::endl;
    }
}

static void printServer(const ServerConfig& serv, size_t index)
{
    std::cout << "\nServer #" << index << std::endl;

    std::cout << "  host: " << serv.getHost() << std::endl;
    std::cout << "  port: " << serv.getPort() << std::endl;

    if (!serv.getServerNames().empty())
    {
        std::cout << "  server_name:";
        const std::vector<std::string>& names = serv.getServerNames();
        for (size_t i = 0; i < names.size(); ++i)
            std::cout << " " << names[i];
        std::cout << std::endl;
    }

    if (!serv.getRoot().empty())
        std::cout << "  root: " << serv.getRoot() << std::endl;

    if (!serv.getIndex().empty())
    {
        std::cout << "  index:";
        const std::vector<std::string>& index = serv.getIndex();
        for (size_t i = 0; i < index.size(); ++i)
            std::cout << " " << index[i];
        std::cout << std::endl;
    }

    std::cout << "  client_max_body_size: "
              << serv.getClientMaxBodysize()
              << std::endl;

    if (!serv.getErrorPages().empty())
    {
        std::cout << "  error_page:" << std::endl;
        const std::map<int, std::string>& errors = serv.getErrorPages();
        for (std::map<int, std::string>::const_iterator it = errors.begin();
             it != errors.end(); ++it)
            std::cout << "    "
                      << it->first << " -> "
                      << it->second << std::endl;
    }

    const std::vector<LocationConfig>& locations = serv.getLocations();
    for (size_t i = 0; i < locations.size(); ++i)
        printLocation(locations[i]);
}

void printServers(const std::vector<ServerConfig>& servers)
{
    for (size_t i = 0; i < servers.size(); ++i)
        printServer(servers[i], i);
}