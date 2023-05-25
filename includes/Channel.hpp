#pragma once

#include "Client.hpp"
#include "Server.hpp"
#include <string>
#include <vector>
#include <algorithm>

class Client;
class Server;

enum ChannelModes {
	NONE = 0,
	INVITE_ONLY = 1 << 3,
	TOPIC_PROTECTED = 1 << 4,
	LIMITED = 1 << 7,
	COPE = 1 << 8,
	KEY = 1 << 10,
};

class Channel
{
	private:
		Server					&_server;
		std::string				_name;
		std::string				_topic;
		std::string				_key;
		size_t					_limit;
		std::vector<Client *>	_clients;
		std::vector<Client *>	_invited;
		std::vector<Client *>	_operators;
		Client					*_creator;
		int						_modes;
		time_t					_created_at;

		void	addToVector(std::vector<Client *> &vec, Client *client);
		void	removeFromVector(std::vector<Client *> &vec, Client *client);
		bool	isInVector(std::vector<Client *> &vec, Client *client);

	public:
		Channel(std::string name, Server &server, Client *creator = NULL);
		~Channel();

		const std::string	getName() const { return _name; };
		const std::string	getTopic() const { return _topic; };
		const std::string	getKey() const { return _key; };
		std::vector<Client *>	getClients() { return _clients; };
		std::string			getNamesClients();
		Client				*getClientByNick(const std::string nickname);
		Client				*getClientByUser(const std::string username);
		Client				*getCreator() { return _creator; };
		int					&getMode() { return _modes; };
		time_t				getCreationDate() const { return _created_at; };
		size_t				getLimit() const { return _limit; };

		void	setName(const std::string name) { _name = name; };
		void	setTopic(const std::string topic) { _topic = topic; };
		void	setKey(const std::string key) { _key = key; };
		void	setLimit(size_t limit) { _limit = limit; };
		void	setCreator(Client *creator) { _creator = creator; };

		void	send_message(const std::string message, Client *except = NULL);

		// clients related
		void	addClient(Client *client) { addToVector(_clients, client); };
		/* void	removeClient(Client *client) { removeFromVector(_clients, client); removeOperator(client); }; */
		void	removeClient(Client *client);
		bool 	isClient(Client *client) { return isInVector(_clients, client); };
		void	addInvitation(Client *client) { addToVector(_invited, client); };
		void	removeInvitation(Client *client) { removeFromVector(_invited, client); };
		bool	isInvited(Client *client) { return isInVector(_invited, client); };
		void	addOperator(Client *client) { addToVector(_operators, client); };
		void	removeOperator(Client *client) { removeFromVector(_operators, client); };
		bool	isOperator(Client *client) { return isInVector(_operators, client); };
		bool	isCreator(Client *client) { return _creator == client; };

		// modes related
		void	addMode(ChannelModes mode) { _modes |= mode; };
		void	removeMode(ChannelModes mode) { _modes &= ~mode; };
		void	toggleMode(ChannelModes mode) { _modes ^= mode; };
		bool	isModeSet(ChannelModes mode) { return _modes & mode; };
};
