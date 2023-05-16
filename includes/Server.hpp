#pragma once

// standard lib
#include <string>
#include <algorithm>
#include <map>
#include <vector>

// external lib
#include <sys/socket.h> // socket(), setsocketopt(), bind(), listen()
#include <netinet/in.h> // struct sockaddr_in
#include <sys/epoll.h> // struct epool_event
#include <arpa/inet.h> // inet_ntoa

// custom lib
#include "Client.hpp"
#include "define.hpp"
#include "utils.hpp"

class Server
{
	private:
		Server(){};
		void _createsocket();
		void _bindsocket();
		void _createpoll();
		void _handle_connection();
		void _handle_new_msg(int i);

		// member attributes
		int 							_port;
		std::string						_password;
		int								_socket_fd;
		struct sockaddr_in				_socket_addr;
		int								_epoll_fd;
		struct epoll_event				_epoll_event;
		struct epoll_event				_epoll_tab_events[MAX_EVENTS];
		std::map<int, Client*>			_vector_clients;
		std::map<std::string, void (*)(Client &, std::string &)>	_commands;

	public:
		Server(int port, std::string password);
		~Server();
		void	run_server();
};

/* class CustomException : public std::exception { */
/* 	private: */
/* 		const char* m_message; */
/* 	public: */
/* 		CustomException(const char * message): m_message(message) {}; */
/* 		CustomException(std::string message, int code) { */
/* 			// doesn't work because the message is freed before the throw */
/* 			if (errno != 0) */
/* 				message = message + ": " + strerror(code); */
/* 			m_message = message.c_str(); */
/* 		} */
/* 		virtual const char* what() const throw() { return m_message; }; */
/* }; */
