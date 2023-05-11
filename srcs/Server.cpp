#include "../includes/Server.hpp"
#include <asm-generic/socket.h>
#include <sys/socket.h>

Server::Server(int port, std::string password) : _port(port), _password(password) {
	if ((_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		throw CustomException("Error: Cannot create socket");
	int optval = 1;
	if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
		throw CustomException("Error: Cannot set socket");

};
