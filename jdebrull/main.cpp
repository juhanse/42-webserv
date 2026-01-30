/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:21:26 by Jdebrull          #+#    #+#             */
/*   Updated: 2026/01/27 19:03:06 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config/ConfigParser.hpp"

int	main(int ac, char **av)
{
	ConfigParser	parser;
	if (ac != 2)
	{
		std::cerr	<< "Use ./webserv config.conf " << std::endl;
		return (0);
	}
	
	parser.parse(av[1]);
	return (0);
}