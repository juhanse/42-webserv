#ifndef PARSELISTEN_HPP
# define PARSELISTEN_HPP

#include "ConfigParser.hpp"

void	parseListen(std::vector<std::string>& tokens, size_t& i, ServerConfig& serv, bool& listen_set);

#endif