/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseListen.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:02:34 by Jdebrull          #+#    #+#             */
/*   Updated: 2026/01/31 17:31:22 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseListen.hpp"

static void	assignPort(const char* str, size_t& i, Server& serv)
{
	int port = 0;

	if (!isDigit(str[i]))
		throw (std::runtime_error("Port must be numeric"));
	if (str[i] == '0' && isDigit(str[i + 1]))
		throw (std::runtime_error("Port can't have leading zero's."));
	while (str[i])
	{
		if (!isDigit(str[i]))
			throw (std::runtime_error("Port can only contain digits."));
		port = port * 10 + (str[i] - '0');
		if (port > 65535)
			throw (std::runtime_error("Port is out of range max = 65535."));
		i++;
	}
	if (port < 1)
		throw (std::runtime_error("Port can't be smaller than 1."));
	serv.port = port;
}

static bool	checkIpAddress(const char *str)
{
	int dots = 0;
	int	num = -1;

	if (!str)
		return (false);
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '0' && str[i + 1] && isDigit(str[i + 1]) && num == -1)
			throw std::runtime_error("Ip address numbers cannot contain leading zeros.");
			
		if (isDigit(str[i])) {
			if (num == -1)
				num = 0;
			num = (num * 10) + (str[i] - '0');
			if (num > 255)
				throw (std::runtime_error("Ip address numbers can only go up to 255."));
		}
		else if (str[i] == '.') {
			if (num == -1)
				return (false);
			dots++;
			num = -1;
		}
		else if (str[i] == ':') {
			if (dots != 3 || num == -1)
				throw std::runtime_error("Wrong Ip address format.");
			return (true);
		}
		else
			return (false);
	}
	return (dots == 3 && num != -1);
}

static void	checkIpPort(const char* str, Server& serv, size_t count)
{

	size_t i = 0;

	if (!str)
		throw (std::runtime_error("Missing value for listen directive."));
	if (count == 0) {
		assignPort(str, i, serv);
	}
	else if (count == 1)
	{
		if (str[0] == ':')
		{
			i++;
			assignPort(str, i, serv);
		}
		else {
			while (str[i]) {
				if (str[i] == ':')
					break ;
				i++;
			}
			if (!checkIpAddress(str))
				throw (std::runtime_error("Invalid ip address for listen directive."));
			serv.host.assign(str, i);
			i++;
			assignPort(str, i, serv);
		}
	}
	else
		throw (std::runtime_error("Wrong Ip address and port format."));
}

void	parseListen(std::vector<std::string>& tokens, size_t& i, Server& serv)
{
	if (serv.port)
		throw (std::runtime_error("Multiple listen directives is not allowed."));
	i++;
	if (i >= tokens.size() || tokens[i] == ";")
		throw (std::runtime_error("Expected value after listen"));
	
	size_t count = 0;
	for (size_t j = 0; j < tokens[i].size(); ++j)
	{
		if (tokens[i][j] == ':')
			count++;
	}
	const char* str = tokens[i].c_str();
	for (size_t j = 0; str[j]; j++) {
		if ((str[j] != '.' && str[j] != ':' && !isDigit(str[j])))
			throw (std::runtime_error("Invalid characters in Ip adress or port directive."));
	}
	checkIpPort(str, serv , count);
	i++;
	if (i >= tokens.size() || tokens[i] != ";")
		throw (std::runtime_error("Expected a ';' after listen directive."));
	i++;
}

// void	parseListen(std::vector<std::string>& tokens, size_t& i, Server& serv)
// {
// 	if (serv.port != 0)
// 		throw (std::runtime_error("Multiple listen directives is not allowed."));
// 	i++;
// 	if (i >= tokens.size() || tokens[i] == ";")
// 		throw (std::runtime_error("Expected value after listen"));

// 	const char *str = tokens[i].c_str();
// 	for (size_t j = 0; str[j]; j++) {
// 		if ((str[j] != '.' && str[j] != ':' && !isDigit(str[j])))
// 			throw (std::runtime_error("Invalid characters in Ip adress or port directive."));
// 	}
// 	if (!checkIpAddress(str))
// 		throw (std::runtime_error("Invalid ip address for listen directive."));
// 	if (!checkIpPort(str, serv))
// 		throw (std::runtime_error("Invalid port address for listen directive."));
// 	i++;
// 	if (i >= tokens.size() || tokens[i] != ";")
// 		throw (std::runtime_error("Expected a ';' after listen directive."));
// 	i++;
// }