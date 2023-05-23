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

void	Channel::send_message(const std::string message) {
	std::vector<Client*>::iterator it = _clients.begin();
	while (it != _clients.end()) {
		(*it)->send_message(message);
		it++;
	}
}
