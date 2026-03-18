/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:49:08 by jdebrull          #+#    #+#             */
/*   Updated: 2026/03/18 13:49:08 by jdebrull         ###   ########.fr       */
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
#include "../config/ServerConfig.hpp"
#include "../config/LocationConfig.hpp"
#include "../utils/utils.hpp"
#include "ParseListen.hpp"
#include "ParseServerName.hpp"
#include "ParseRoot.hpp"
#include "ParseIndex.hpp"
#include "ParseMaxSize.hpp"
#include "ParseErrorPage.hpp"
#include "ParseLocation.hpp"
#include "../utils/debugPrint.hpp"

class ConfigParser {
	public:
		std::vector<ServerConfig> parse(const std::string& filename);
		std::vector<std::string> tokenize(const std::string& input);
};

#endif