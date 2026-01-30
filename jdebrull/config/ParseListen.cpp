/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseListen.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:02:34 by Jdebrull          #+#    #+#             */
/*   Updated: 2026/01/28 14:28:00 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParseListen.hpp"

static bool	checkIpPort(const char* str, Server& serv)
{
	int port = 0;
	int i = 0;
	
	if (!str)
		return (0);
	while (str[i]) {
		if (str[i] == ':')
			break ;
		i++;
	}
	if (str[i] != ':')
		throw (std::runtime_error("Missing ':' between Ip adress and port."));
	serv.host.assign(str, i);
	i++;
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
			throw (std::runtime_error("Port is out of range max (65535)."));
		i++;
	}
	if (port < 1)
		throw (std::runtime_error("Port can't be smaller than 1."));
	serv.port = port;
	return (true);
}

static bool	checkIpAdress(const char *str)
{
	int dots = 0;
	int	num = -1;

	if (!str)
		return (false);
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '0' && str[i + 1] && isDigit(str[i + 1]) && num == -1)
			throw std::runtime_error("Ip adress numbers cannot contain leading zeros.");
			
		if (isDigit(str[i])) {
			if (num == -1)
				num = 0;
			num = (num * 10) + (str[i] - '0');
			if (num > 255)
				throw (std::runtime_error("Ip adress numbers can only go up to 255."));
		}
		else if (str[i] == '.') {
			if (num == -1)
				return (false);
			dots++;
			num = -1;
		}
		else if (str[i] == ':') {
			if (dots != 3 || num == -1)
				throw std::runtime_error("Wrong Ip adress format.");
			return (true);
		}
		else
			return (false);
	}
	return (dots == 3 && num != -1);
}

bool	parseListen(std::string tokens, Server& serv)
{
	const char *str = tokens.c_str();

	for (size_t j = 0; str[j]; j++) {
		if ((str[j] != '.' && str[j] != ':' && !isDigit(str[j])))
			throw (std::runtime_error("Invalid Ip adress or port for config file."));
	}
	if (!checkIpAdress(str))
		return (false);
	if (!checkIpPort(str, serv))
		return (false);
	return (true);
}