#include "../includes/Client.hpp"
#include <algorithm>

Client::Client(int client_fd, std::string hostname) :
	_client_fd(client_fd),
	_hostname(hostname),
	_active_channel(NULL),
	_modes(0),
	_isRegistered(false),
	_isAuth(true) // TODO: change to false
{
		std::cout << "new client with fd: " << _client_fd << std::endl;
};

Client::~Client() {
	leaveAllChannels();
}

Channel*	Client::getChannel(const std::string channel_name) {
	std::vector<Channel*>::iterator it = _channels.begin();
	while (it != _channels.end()) {
		if ((*it)->getName() == channel_name)
			return (*it);
		it++;
	}
	return NULL;
}

void	Client::joinChannel(Channel *channel) {
	channel->addClient(this);
	_channels.push_back(channel);
}

void	Client::leaveChannel(Channel *channel) {
	std::vector<Channel*>::iterator it = std::find(_channels.begin(), _channels.end(), channel);
	if (it == _channels.end())
		return ;
	if (_active_channel == channel)
		_active_channel = NULL;
	(*it)->removeClient(this);
	_channels.erase(it);
}

void	Client::leaveAllChannels() {
	std::vector<Channel*>::iterator it = _channels.begin();
	while (it != _channels.end()) {
		leaveChannel(*it);
	}
	_active_channel = NULL;
}

void	Client::leaveActiveChannel() {
	if (!_active_channel)
		return ;
	leaveChannel(_active_channel);
	_active_channel = NULL;
}

void	Client::send_message(const std::string message) {
	send(_client_fd, message.c_str(), message.length(), MSG_NOSIGNAL);
	// std::cerr << "client fd: " << _client_fd << std::endl;
}
