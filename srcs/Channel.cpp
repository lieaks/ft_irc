#include "../includes/Channel.hpp"

Channel::Channel(std::string name, std::string topic, Client *creator):
	_name(name),
	_topic(topic),
	_creator(creator),
	_created_at(time(NULL)),
	_limit(10),
	_modes(0)
{
	std::cout << "new channel with name: " << _name << std::endl;
};

Channel::~Channel() {
	std::vector<Client*>::iterator it = _clients.begin();
	while (it != _clients.end())
		(*it)->leaveChannel(this);
};

Client	*Channel::getClient(std::string nickname) {
	std::vector<Client*>::iterator it = _clients.begin();
	while (it != _clients.end()) {
		if ((*it)->getNickname() == nickname)
			return (*it);
		it++;
	}
	return NULL;
}

bool	Channel::addClient(Client *client) {
	std::vector<Client*>::iterator it = std::find(_clients.begin(), _clients.end(), client);
	if (it != _clients.end())
		return false;
	// TODO: check that the user is not banned or has the right to join
	_clients.push_back(client);
	// TODO: send join message to channel
	return true;
}

void	Channel::removeClient(Client *client) {
	std::vector<Client*>::iterator it = std::find(_clients.begin(), _clients.end(), client);
	if (it == _clients.end())
		return ;
	_clients.erase(it);
	// TODO: send leave message to channel
}

void	Channel::send_message(const std::string message) {
	std::vector<Client*>::iterator it = _clients.begin();
	while (it != _clients.end()) {
		(*it)->send_message(message);
		it++;
	}
}

void	Channel::addOperator(Client *client) {
	std::vector<Client*>::iterator it = std::find(_operators.begin(), _operators.end(), client);
	if (it != _operators.end())
		return ;
	_operators.push_back(client);
}
