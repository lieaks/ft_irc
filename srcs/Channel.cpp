#include "../includes/Channel.hpp"
#include <vector>

Channel::Channel(std::string name, std::string topic, Client *creator):
	_name(name),
	_topic(topic),
	_limit(10),
	_creator(creator),
	_modes(0),
	_created_at(time(NULL))
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
	_clients.push_back(client);
	return true;
}

void	Channel::removeClient(Client *client) {
	std::vector<Client*>::iterator it = std::find(_clients.begin(), _clients.end(), client);
	if (it == _clients.end())
		return ;
	_clients.erase(it);
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

void	Channel::removeOperator(Client *client) {
	std::vector<Client *>::iterator it = std::find(_operators.begin(), _operators.end(), client);
	if (it == _operators.end())
		return ;
	_operators.erase(it);
}

bool	Channel::isOperator(Client *client) {
	std::vector<Client *>::iterator it = std::find(_operators.begin(), _operators.end(), client);
	if (it == _operators.end())
		return false;
	return true;
}

void	Channel::addBan(Client *client) {
	std::vector<Client *>::iterator it = std::find(_banned.begin(), _banned.end(), client);
	if (it != _banned.end())
		return ;
	_banned.push_back(client);
}

void	Channel::removeBan(Client *client) {
	std::vector<Client *>::iterator it = std::find(_banned.begin(), _banned.end(), client);
	if (it == _banned.end())
		return ;
	_banned.erase(it);
}

bool	Channel::isBanned(Client *client) {
	std::vector<Client *>::iterator it = std::find(_banned.begin(), _banned.end(), client);
	if (it == _banned.end())
		return false;
	return true;
}
