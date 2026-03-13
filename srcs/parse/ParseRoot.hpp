#ifndef PARSEROOT_HPP
# define PARSEROOT_HPP

#include "ConfigParser.hpp"

bool	isValidPath(const std::string& token);

template <typename T>
void	parseRoot(const std::vector<std::string>& tokens, size_t& i, T& config, bool& root_set)
{
	if (root_set)
		throw (std::runtime_error("Duplicate root directive is not allowed in the same block."));

	i++;
	if (i >= tokens.size())
		throw (std::runtime_error("Expected path after root."));

	if (!isValidPath(tokens[i]))
		throw (std::runtime_error("Invalid root path."));
	config.setRoot(tokens[i]);

	i++;
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Missing ';' after root directive."));

	root_set = true;
	i++;
}

#endif