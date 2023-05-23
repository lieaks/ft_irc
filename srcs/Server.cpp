#include "../includes/Server.hpp"

Server::Server(int port, std::string password, std::string operators_password):
	_port(port), _running(true), _password(password), _operators_password(operators_password) {
		if (_operators_password.empty())
			_operators_password = DEFAULT_OPER_PASS;
		_createsocket();
		_bindsocket();
		if (listen(_socket_fd, BACKLOG) < 0)
			throw std::runtime_error("Error: Cannot listen");
		_createpoll();
		_init_commands();
	};

Server::~Server() {
	std::map<int, Client*>::iterator clit = _vector_clients.begin();
	while (clit != _vector_clients.end()) {
		close(clit->first);
		delete clit->second;
		clit++;
	}
	std::vector<Channel *>::iterator chit = _vector_channels.begin();
	while (chit != _vector_channels.end()) {
		delete *chit;
		chit++;
	}
};

Client	*Server::getClientByNick(const std::string nickname) {
	std::map<int, Client *>::iterator it = _vector_clients.begin();
	while (it != _vector_clients.end()) {
		if ((it->second)->getNickname() == nickname)
			return it->second;
		it++;
	}
	return NULL;
}

Client	*Server::getClientByUser(const std::string username) {
	std::map<int, Client *>::iterator it = _vector_clients.begin();
	while (it != _vector_clients.end()) {
		if ((it->second)->getUsername() == username)
			return it->second;
		it++;
	}
	return NULL;
}

Channel *Server::getChannelByName(const std::string name) {
	std::vector<Channel *>::iterator it = _vector_channels.begin();
	while (it != _vector_channels.end()) {
		if ((*it)->getName() == name)
			return *it;
		it++;
	}
	return NULL;
}

void	Server::removeClient(Client *client) {
	if (!client)
		return;
	std::map<int, Client *>::iterator it = _vector_clients.begin();
	while (it != _vector_clients.end()) {
		if (it->second == client) {
			client->leaveAllChannels();
			delete client;
			close(it->first);
			_vector_clients.erase(it);
			return ;
		}
		it++;
	}
}

void	Server::addChannel(Channel	*channel) {
	if (!channel)
		return;
	std::vector<Channel *>::iterator it = _vector_channels.begin();
	while (it != _vector_channels.end()) {
		if ((*it)->getName() == channel->getName())
			return ;
		it++;
	}
	_vector_channels.push_back(channel);
}

void	Server::removeChannel(Channel *channel) {
	if (!channel)
		return;
	std::vector<Channel *>::iterator it = _vector_channels.begin();
	while (it != _vector_channels.end()) {
		if (*it == channel) {
			delete *it;
			_vector_channels.erase(it);
			return ;
		}
		it++;
	}
}

void Server::_createsocket() {
	// AF_INET = addr ip v4 || SOCK_STREAM = protocol TCP 
	if ((_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
		throw std::runtime_error("Error: Cannot create socket");
	int optval = 1;
	if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR,
				&optval, sizeof(optval)) < 0)
		throw std::runtime_error("Error: Cannot set socket");
};

void Server::_bindsocket() {
	_socket_addr.sin_family = AF_INET;
	_socket_addr.sin_addr.s_addr = INADDR_ANY; // "127.0.0.1"
	_socket_addr.sin_port = htons(_port);
	memset(_socket_addr.sin_zero, 0, sizeof(_socket_addr.sin_zero));
	if (bind(_socket_fd, reinterpret_cast<struct sockaddr *>(&_socket_addr),
				sizeof(struct sockaddr)) < 0)
		throw std::runtime_error("Error: Cannot bind");
}

void Server::_createpoll(){
	if ((_epoll_fd = epoll_create(BACKLOG)) < 0)
		throw std::runtime_error("Error: Cannot create epoll");
	_epoll_event.data.fd = _socket_fd;
	_epoll_event.events = EPOLLIN;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, _socket_fd, &_epoll_event) < 0)
		throw std::runtime_error("Error: Cannot control epoll");
};

void Server::run_server() {
	int	new_event_fd;
	while (_running) {
		new_event_fd = epoll_wait(_epoll_fd, _epoll_tab_events, MAX_EVENTS, -1);
		for (int i = 0; i < new_event_fd; i++){
			if (_epoll_tab_events[i].data.fd == _socket_fd)
				_handle_connection();					
			else
				_handle_new_msg(i);
		}
		// ping();
	}
};

void Server::_handle_connection() {
	int					client_d;
	struct sockaddr_in	client_addr;
	socklen_t			client_addr_len;

	// accept the connection request by the client
	memset(&client_addr, 0, sizeof(client_addr));
	memset(&client_addr_len, 0, sizeof(client_addr_len));
	if ((client_d = accept(_socket_fd,
					reinterpret_cast<struct sockaddr*>(&client_addr), &client_addr_len)) < 0)
		throw std::runtime_error("Error: Cannot accept connection");

	// fill the socket adress with getsockname() + add new client to vector
	getsockname(client_d, reinterpret_cast<struct sockaddr*>(&client_addr),
			&client_addr_len); 
	// _vector_clients.push_back(new Client(client_d, inet_ntoa(client_addr.sin_addr)));
	_vector_clients.insert(std::make_pair(client_d,
				new Client(client_d, inet_ntoa(client_addr.sin_addr))));

	// add client_d to the poll
	_epoll_event.data.fd = client_d;
	_epoll_event.events = EPOLLIN;
	if (epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, client_d, &_epoll_event) < 0)
		throw std::runtime_error("Error: Cannot control epoll");
};

void Server::_handle_new_msg(int i) {
	char	buffer[BUFFER_SIZE];
	std::string input_buf;
	int		ret;
	Client* client;
	int		client_socket;

	std::map<int, Client*>::iterator it = _vector_clients.find(_epoll_tab_events[i].data.fd);
	client = it->second;
	client_socket = client->getFd();
	memset(buffer, 0, BUFFER_SIZE);
	if ((ret = recv(_epoll_tab_events[i].data.fd, buffer, BUFFER_SIZE, 0)) < 0)
		throw std::runtime_error("Error: read msg");
	else if (ret == 0) {
		// disconnect
		removeClient(client);
	} else {
		std::string	cmd;
		std::vector<std::string> args;

		input_buf = client->getInput() + buffer;
		client->setInput(input_buf);
		size_t pos = client->getInput().find_first_of("\r\n");
		while (pos != std::string::npos) {
			cmd = client->getInput().substr(0, pos);
			if (client->getInput().size() > pos + 1 && client->getInput()[pos + 1] == '\n')
				pos++;
			client->setInput(client->getInput().substr(pos + 1));
			std::cout << "cmd: " << cmd << std::endl;
			args = split(cmd, " ");
			if (args.size()) {
				if (_commands.find(ft_toupper(args[0])) != _commands.end())
					_commands[ft_toupper(args[0])](*this, *client, args);
				else // TODO: uncomment this ?
					client->send_message(ERR_UNKNOWNCOMMAND(client->getNickname(), args[0]));
			}
			else
				client->send_message(ERR_UNKNOWNCOMMAND(client->getNickname(), args[0]));

			if (_vector_clients.find(client_socket) == _vector_clients.end()) 
				return;
			pos = client->getInput().find_first_of("\r\n");
		}
	}
};

void	Server::_init_commands( void ) {
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("NICK", &cmd_nick));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("USER", &cmd_user));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("PASS", &cmd_pass));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("INVITE", &cmd_invite));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("PING", &cmd_ping));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("INFO", &cmd_info));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("VERSION", &cmd_version));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("TIME", &cmd_time));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("OPER", &cmd_oper));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("NOTICE", &cmd_notice));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("PRIVMSG", &cmd_privmsg));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("WALLOPS", &cmd_wallops));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("QUIT", &cmd_quit));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("CAP", &cmd_cap));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("JOIN", &cmd_join));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("DIE", &cmd_die));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("MODE", &cmd_mode));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("TOPIC", &cmd_topic));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("KICK", &cmd_kick));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("PART", &cmd_part));
	_commands.insert(std::pair<std::string, bool (*)(Server&, Client&, std::vector<std::string>&)>("NAMES", &cmd_part));
}
