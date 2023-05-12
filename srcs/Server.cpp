#include "../includes/Server.hpp"
#include <asm-generic/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>

Server::Server(int port, std::string password) : _port(port), _password(password) {
	_createsocket();
	_bindsocket();
	if (listen(_socket_fd, BACKLOG) < 0)
		throw CustomException("Error: Cannot listen");
	_createpoll();
};

Server::~Server() {};

void Server::_createsocket(){
	if ((_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		throw CustomException("Error: Cannot create socket");
	int optval = 1;
	if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
		throw CustomException("Error: Cannot set socket");
};

void Server::_bindsocket(){
	_socket_addr.sin_family = AF_INET;
	_socket_addr.sin_addr.s_addr = INADDR_ANY;
	_socket_addr.sin_port = htons(_port);
	memset(_socket_addr.sin_zero, 0, sizeof(_socket_addr.sin_zero));
	if (bind(_socket_fd, reinterpret_cast<struct sockaddr *>(&_socket_addr), sizeof(struct sockaddr)) < 0)
		throw CustomException("Error: Cannot bind");
}

void Server::_createpoll(){
	if ((_epoll_fd = epoll_create(BACKLOG)) < 0)
		throw CustomException("Error: Cannot create epoll");
	_epoll_event.data.fd = _socket_fd;
	_epoll_event.events = EPOLLIN;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _socket_fd, &_epoll_event) < 0)
		throw CustomException("Error: Cannot control epoll");
};
