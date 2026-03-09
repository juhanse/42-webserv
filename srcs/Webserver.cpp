#include "Webserver.hpp"

Webserver::Webserver(std::vector<ServerConfig*> configs): _configs(configs) {}

Webserver::~Webserver() {
	for (std::map<int, Client*>::iterator it = _clients.begin(); 
			it != _clients.end(); ++it) //check post or pre inc
				delete it->second;
			_clients.clear();
	
	for (size_t i = 0; i < _pollWatch.size(); i++)
		close(_pollWatch[i].fd);
}

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

int	Webserver::newListenSock(int port) {
	int	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
		return (perror("socket()"), -1);
	
	int	option = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1)
		return (perror("setsockopt()"), close(fd), -1);
	
	if (setNonBlock(fd) == -1)
		return (close(fd), -1);
	
	struct sockaddr_in	addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(fd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) == -1)
		return (perror("bind()"), close(fd), -1);
	
	if (listen(fd, SOMAXCONN) == -1)
		return (perror("listen()"), close(fd), -1);
	
	return (fd);
}

bool	Webserver::isListenSock(int fd) {
	if (_listenFds.find(fd) != _listenFds.end())
		return (true);
	return (false);
}

void	Webserver::newClient(int listFd) {
	ServerConfig*	config = _listenFds[listFd];

	struct sockaddr_in	client_addr;
	socklen_t sockLen = sizeof(client_addr);
	int	client_fd = accept(listFd, reinterpret_cast<sockaddr *>(&client_addr), &sockLen); //protect it?
	setNonBlock(client_fd); //define what to do in case of failure?

	// char* ip = inet_ntoa(client_addr.sin_addr);
	// int port = ntohs(client_addr.sin_port);
	Client*	client = new Client(client_fd); //add ip, port, config ?
	_clients[client_fd] = client;

	sendToWatchList(client_fd);
	std::cout << "New client " << client_fd << " connected" << std::endl;
}

void	Webserver::closeClient(int fd) {
	std::map<int, Client*>::iterator it_map = _clients.find(fd);
	if (it_map != _clients.end()) {
		delete it_map->second;
		_clients.erase(it_map);
	}

	for (std::vector<pollfd>::iterator it_vec = _pollWatch.begin();
			it_vec != _pollWatch.end() ; it_vec++) {
		if (it_vec->fd == fd) {
			_pollWatch.erase(it_vec);
			break ;
		}
	}
	std::cout << "Client " << fd << " disconnected" << std::endl;
	close(fd);
}

int Webserver::newServ(ServerConfig* config) {	
	int	listen_fd = newListenSock(config->getPort());
	if (listen_fd == -1) {
		std::cerr	<< "Listen socket creation failed on port "
					<< config->getPort() << std::endl;
		return (-1);	
	}
	sendToWatchList(listen_fd);
	_listenFds[listen_fd] = config;
	
	std::cout << "Server listening on port " << config->getPort() << std::endl;

	return (0);
}

void	Webserver::switchToPollout(int fd) {
	for (size_t i = 0; i < _pollWatch.size(); i++) {
		if (_pollWatch[i].fd == fd) {
			_pollWatch[i].events = POLLOUT;
			return ;
		}
	}
}

void	Webserver::sendResponse(int fd) {
	std::map<int, Client*>::iterator it = _clients.find(fd);
	if (it == _clients.end())
		return ;

	Client* client = it->second;
	client->writeResponse();
	if (_clients[fd]->getStatus() == DONE)
		closeClient(fd);
}

void	Webserver::receiveRequest(int fd) {
	std::map<int, Client*>::iterator it = _clients.find(fd);
	if (it == _clients.end())
		return ;
	
	Client* client = it->second;
	if (client->getStatus() == DONE)
		closeClient(fd);

	if (client->getStatus() == READING)
		client->readRequest();

	if (client->getStatus() == PROCESSING)
		client->processRequest(); //full parsing Http

	if (client->getStatus() == WRITING)
		switchToPollout(fd);
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

void	Webserver::runServ() {
	while (true) {
		int isReady = poll(_pollWatch.data(), _pollWatch.size(), 3000);

		if (isReady == -1) {
			if (errno == EINTR) //Signal or CGI disturbed poll -> relaunch loop
				continue ;
			perror("poll()"); //something else bad happened
			break ;
		}

		if (isReady == 0) {
			closeTimedOut();
			continue ;
		}

		else {
			for (int i = 0; i < _pollWatch.size(); i++) {
				int		fd = _pollWatch[i].fd;
				short	revents = _pollWatch[i].revents;
				bool	isListen = isListenSock(fd);

				if (!revents)
					continue ;

				if (revents & (POLLHUP | POLLERR | POLLNVAL)) {
					if (!isListen) {
						closeClient(fd);
						continue ;
					}
				}

				if (revents & POLLIN) {
					if (isListen)
						newClient(fd);
					else
						receiveRequest(fd);
				}

				else if (revents & POLLOUT)
					sendResponse(fd);
			}
		}
	}
}
