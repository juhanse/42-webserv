#pragma once

#include <string>
#include <vector>
#include <map>

struct Location {
    std::string              path;
    std::string              root;
    std::vector<std::string> methods;
    std::string              index;
    bool                     autoindex;
    std::string              cgi_path;
    std::string              cgi_ext;
    std::string              upload_dir;
};

struct ServerConfig {
    int                        port;
    std::string                host;
    std::string                root;
    std::map<int, std::string> error_pages;
    std::vector<Location>      locations;
    long                       max_body_size;
};
