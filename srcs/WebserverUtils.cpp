#include "Webserver.hpp"

int	Webserver::setNonBlock(int fd) {
	int	flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1 || fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
		return (perror("fcntl()"), -1);
	return (0);
}

void	Webserver::sendToWatchList(int fd) {
	pollfd	newFd = {fd, POLLIN, 0};
	_pollWatch.push_back(newFd);
}

bool	Webserver::isListenSock(int fd) {
	if (_listenFds.find(fd) != _listenFds.end())
		return (true);
	return (false);
}

void	Webserver::switchToPollout(int fd) {
	for (size_t i = 0; i < _pollWatch.size(); i++) {
		if (_pollWatch[i].fd == fd) {
			_pollWatch[i].events = POLLOUT;
			return ;
		}
	}
}

void	Webserver::closeTimedOut() {
	for (std::map<int, Client*>::iterator it = _clients.begin();
		it != _clients.end(); ) {
			if (it->second->hasTimedOut()) {
				std::cout << "Client " << it->first << " has timed out" << std::endl;
				int fd = it->first;
				++it;
				closeClient(fd);
			}
			else
				++it;
		}
}

