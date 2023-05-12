#pragma once

// standard lib
#include <string>
#include <map>

// external lib
#include <sys/socket.h> // socket(), setsocketopt(), bind(), listen()
#include <netinet/in.h> // struct sockaddr_in
#include <sys/epoll.h> // struct epool_event

// custom lib
#include "Client.hpp"
#include "define.hpp"

class Server
{
private:
	Server(){};
	void _createsocket();
	void _bindsocket();
	void _createpoll();
	// member attributes
	int 							_port;
	std::string						_password;
	int								_socket_fd;
	struct sockaddr_in				_socket_addr;
	int								_epoll_fd;
	struct epoll_event				_epoll_event;
	std::map<std::string, Client*>	_server;

public:
	Server(int port, std::string password);
	~Server();
};

class CustomException : public std::exception {
	private:
		const char* m_message;
	public:
		CustomException(const char * message) : m_message(message) {};
		virtual const char* what() const throw() {return m_message;};
};
