/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebserverCGI.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhanse <juhanse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:59:21 by juhanse           #+#    #+#             */
/*   Updated: 2026/03/18 13:59:21 by juhanse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserver.hpp"

void	Webserver::registerCgi(Client* client, int pipeFd, pid_t pid) {
	CgiData data;
	data.client = client;
	data.pid = pid;
	data.startTime = time(NULL);
	data.output = "";
	
	_cgiMap[pipeFd] = data;

	struct pollfd pfd;
	pfd.fd = pipeFd;
	pfd.events = POLLIN;
	pfd.revents = 0;
	_pollWatch.push_back(pfd);
}

void	Webserver::readCgi(int fd) {
	char buffer[4096];
	int bytesRead = read(fd, buffer, sizeof(buffer));

	if (bytesRead > 0) {
		_cgiMap[fd].output.append(buffer, bytesRead);
	} else if (bytesRead == 0) {
		handleCgiEnd(fd);
	}
}

void	Webserver::handleCgiEnd(int fd) {
	CgiData data = _cgiMap[fd];
	int status;
	
	waitpid(data.pid, &status, WNOHANG);

	int code = 200;
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
		code = 502;
	}

	data.client->parseCgiOutput(data.output, code);
	switchToPollout(data.client->getFd());
	
	removeFromPollWatch(fd);
	close(fd);
	_cgiMap.erase(fd);
}

void	Webserver::checkCgiTimeouts() {
	time_t now = time(NULL);
	std::map<int, CgiData>::iterator it = _cgiMap.begin();

	while (it != _cgiMap.end()) {
		if (now - it->second.startTime > 5) {
			int fd = it->first;
			CgiData data = it->second;

			kill(data.pid, SIGKILL);
			waitpid(data.pid, NULL, WNOHANG);

			data.client->parseCgiOutput("", 504);
			switchToPollout(data.client->getFd());

			removeFromPollWatch(fd);
			close(fd);
			
			std::map<int, CgiData>::iterator toErase = it;
			++it;
			_cgiMap.erase(toErase);
		} else {
			++it;
		}
	}
}

void	Webserver::removeFromPollWatch(int fd) {
	for (std::vector<pollfd>::iterator it = _pollWatch.begin(); it != _pollWatch.end(); ++it) {
		if (it->fd == fd) {
			_pollWatch.erase(it);
			break;
		}
	}
}
