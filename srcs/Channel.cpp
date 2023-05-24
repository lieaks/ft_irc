#include "../includes/Channel.hpp"
#include <vector>

Channel::Channel(std::string name, Server &server, Client *creator):
	_server(server),
	_name(name),
	_limit(10),
	_creator(creator),
	_modes(0),
	_created_at(time(NULL))
{
	std::cout << "new channel with name: " << _name << std::endl;
};

Channel::~Channel() {
	std::vector<Client*>::iterator it = _clients.begin();
	while (it != _clients.end()) {
		(*it)->leaveChannel(this);
		++it;
	}
};


void	Channel::addToVector(std::vector<Client *> &vec, Client *client) {
	if (!client)
		return ;
	std::vector<Client*>::iterator it = std::find(vec.begin(), vec.end(), client);
	if (it != vec.end())
		return ;
	vec.push_back(client);
}

void	Channel::removeFromVector(std::vector<Client *> &vec, Client *client) {
	if (!client)
		return ;
	std::vector<Client*>::iterator it = std::find(vec.begin(), vec.end(), client);
	if (it == vec.end())
		return ;
	vec.erase(it);
}

bool	Channel::isInVector(std::vector<Client *> &vec, Client *client) {
 	if (!client)
		return false;
	std::vector<Client*>::iterator it = std::find(vec.begin(), vec.end(), client);
	if (it == vec.end())
		return false;
	return true;
}

std::string	Channel::getNamesClients() {
	std::string res;
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); it++) {
		if (*it == _creator)
			res+= "@";
		res += (*it)->getNickname();
		res += " ";
	}
	return res;
}

Client	*Channel::getClientByNick(std::string nickname) {
	std::vector<Client*>::iterator it = _clients.begin();
	while (it != _clients.end()) {
		if ((*it)->getNickname() == nickname)
			return (*it);
		it++;
	}
	return NULL;
}

Client	*Channel::getClientByUser(std::string username) {
	std::vector<Client*>::iterator it = _clients.begin();
	while (it != _clients.end()) {
		if ((*it)->getUsername() == username)
			return (*it);
		it++;
	}
	return NULL;
}

void	Channel::send_message(const std::string message, Client *client) {
	std::vector<Client*>::iterator it = _clients.begin();
	while (it != _clients.end()) {
		if (*it != client)
			(*it)->send_message(message);
		it++;
	}
}

void	Channel::removeClient(Client *client) {
	removeFromVector(_clients, client);
	removeFromVector(_operators, client);
	if (client == _creator)
		_creator = NULL;
	if (_clients.size() == 0 && _operators.size() == 0)
		_server.removeChannel(this);
}
