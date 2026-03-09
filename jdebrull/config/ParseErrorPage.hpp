#ifndef PARSEERRORPAGE_HPP
# define PARSEERRORPAGE_HPP

#include "ConfigParser.hpp"

void	parseErrorPage(std::vector<std::string>& tokens, size_t& i, ServerConfig& serv);
bool	isValidErrorCodePath(const std::string& token);

#endif