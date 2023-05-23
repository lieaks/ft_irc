#pragma once

// standard lib
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <cstring>

// external lib
#include <sys/socket.h> // socket(), setsocketopt(), bind(), listen()
#include <netinet/in.h> // struct sockaddr_in
#include <sys/epoll.h> // struct epool_event
#include <arpa/inet.h> // inet_ntoa
#include <unistd.h> // close()

// custom lib
#include "Channel.hpp"
#include "Client.hpp"
#include "define.hpp"
#include "utils.hpp"
#include "commands.hpp"

class Server
{
	private:
		void _createsocket();
		void _bindsocket();
		void _createpoll();
		void _handle_connection();
		void _handle_new_msg(int i);
		void _init_commands();

		// member attributes
		int 							_port;
		bool							_running;
		std::string						_password;
		std::string						_operators_password;
		int								_socket_fd;
		struct sockaddr_in				_socket_addr;
		int								_epoll_fd;
		struct epoll_event				_epoll_event;
		struct epoll_event				_epoll_tab_events[MAX_EVENTS];
		std::map<int, Client*>			_vector_clients;
		std::vector<Channel *>			_vector_channels;
		std::map<std::string, bool (*)(Server &, Client &, std::vector<std::string> & )>	_commands;

	public:
		Server(int port, std::string password, std::string operators_password = DEFAULT_OPER_PASS);
		~Server();
		void	run_server();

		// getter
		std::map<int, Client*>		&getClients() { return _vector_clients; };
		const std::string			getPassword() const { return _password; };
		const std::string			getOperatorPassword() const { return _operators_password; };
		std::vector<Channel *>		&getChannels() { return _vector_channels; };
		Client						*getClientByNick(const std::string nickname);
		Client						*getClientByUser(const std::string username);
		Channel						*getChannelByName(const std::string name);

		void						setRunning(bool running) { _running = running; };

		void	removeClient(Client *client);
		void	addChannel(Channel *channel);
};
