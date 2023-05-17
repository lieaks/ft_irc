#include "../includes/Client.hpp"
#include <algorithm>

Client::Client(int client_fd, std::string hostname) :
	_client_fd(client_fd),
	_hostname(hostname),
	_nickname(""),
	_active_channel(NULL),
	_password(false)
{
		std::cout << "new client with fd: " << _client_fd << std::endl;
};

Client::~Client()
{
	leaveAllChannels();
}

const bool Client::getPassword() const {
	return _password;
}

Channel*	Client::getChannel(const std::string channel_name)
{
	std::vector<Channel*>::iterator it = _channels.begin();
	while (it != _channels.end()) {
		if ((*it)->getName() == channel_name)
			return (*it);
		it++;
	}
	return NULL;
}

void	Client::setPassword(bool pw) {_password = pw;}

bool	Client::joinChannel(Channel *channel)
{
	if (channel->addClient(this)) {
		_channels.push_back(channel);
		return true;
		// TODO: send join message to client
	}
	// TODO: send error message to client
	std::cout << "failed to add client to channel" << std::endl;
	return false;
}

void	Client::leaveChannel(Channel *channel)
{
	std::vector<Channel*>::iterator it = std::find(_channels.begin(), _channels.end(), channel);
	if (it == _channels.end())
		return ;
	if (_active_channel == channel)
		_active_channel = NULL;
	(*it)->removeClient(this);
	_channels.erase(it);
	// TODO: send leave message to client
}

void	Client::leaveAllChannels()
{
	std::vector<Channel*>::iterator it = _channels.begin();
	while (it != _channels.end()) {
		leaveChannel(*it);
	}
	_active_channel = NULL;
}

void	Client::leaveActiveChannel()
{
	if (!_active_channel)
		return ;
	leaveChannel(_active_channel);
	_active_channel = NULL;
}

void	Client::send_message(const std::string message)
{
	// std::cout << "sending message to client " + _nickname + ": " << message << std::endl;
	send(_client_fd, message.c_str(), message.length(), 0);
}
