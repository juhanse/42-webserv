#include "ParseRoot.hpp"

bool	isValidPath(const std::string& token)
{
	if (token.empty())
		return (false);
	if (token[0] != '/' && token[0] != '.')
		return (false);
	if (token.find("..") != std::string::npos)
		return (false);
	for (size_t i = 0; i < token.size(); ++i)
	{
		char c = token[i];
		if (!isAlNum(c) && c != '/' && c != '_' && c != '-' && c != '.')
			return (false);
	}
	return (true);
}
