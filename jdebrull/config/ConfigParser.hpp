/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:49:45 by jdebrull          #+#    #+#             */
/*   Updated: 2026/01/30 19:08:11 by jdebrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGPARSER_HPP
# define CONFIGPARSER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <climits>
#include "../core/Server.hpp"
#include "../utils/utils.hpp"
#include "ParseListen.hpp"
#include "ParseServerName.hpp"
#include "ParseRoot.hpp"
#include "ParseIndex.hpp"
#include "ParseBodySize.hpp"
#include "ParseErrorPage.hpp"

class ConfigParser {
	public:
		std::vector<Server> parse(const std::string& filename);
		std::vector<std::string> tokenize(const std::string& input);
};

#endif