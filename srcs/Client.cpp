#include "Client.hpp"

Client::Client(int fd): _fd(fd) {}

Client::~Client() {
	//delete	_request;
	//delete	_response;
}

