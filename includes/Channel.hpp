#pragma once

#include "Client.hpp"
#include <string>
#include <vector>
#include <algorithm>

class Client;

class Channel
{
	private:
		std::string				_name;
		std::string				_topic;
		std::vector<Client *>	_clients;
	public:
		Channel(std::string name, std::string topic);
		~Channel();

		const std::string	getName() const { return _name; };
		const std::string	getTopic() const { return _topic; };
		std::vector<Client *>	getClients() { return _clients; };
		Client				*getClient(const std::string nickname);

		void	setName(const std::string name) { _name = name; };
		void	setTopic(const std::string topic) { _topic = topic; };

		// clients related
		bool	addClient(Client *client);
		void	removeClient(Client *client);
		void	send_message(const std::string message);
};
