#pragma once

#include "Client.hpp"
#include <string>
#include <vector>
#include <algorithm>

class Client;

enum ChannelModes
{
	NONE = 0,
	TOPIC = 1 << 0,
	SECRET = 1 << 1,
	NO_EXTERNAL_MSG = 1 << 2,
	MODERATED = 1 << 3,
	INVITE_ONLY = 1 << 4,
	PRIVATE = 1 << 5,
	PASSWORDED = 1 << 6,
};

class Channel
{
	private:
		std::string				_name;
		std::string				_topic;
		std::string				_key;
		size_t					_limit;
		std::vector<Client *>	_clients;
		std::vector<Client *>	_operators;
		Client					*_creator;
		int						_modes;
		time_t					_created_at;

	public:
		Channel(std::string name, std::string topic = "topic", Client *creator = NULL);
		~Channel();

		const std::string	getName() const { return _name; };
		const std::string	getTopic() const { return _topic; };
		const std::string	getKey() const { return _key; };
		std::vector<Client *>	getClients() { return _clients; };
		std::vector<Client *>	getOperators() { return _operators; };
		Client				*getClient(const std::string nickname);
		int					&getMode() { return _modes; };

		void	setName(const std::string name) { _name = name; };
		void	setTopic(const std::string topic) { _topic = topic; };
		void	setKey(const std::string key) { _key = key; };

		// clients related
		bool	addClient(Client *client);
		void	removeClient(Client *client);
		void	send_message(const std::string message);
		void	addOperator(Client *client);

		// modes related
		void	addMode(ChannelModes mode) { _modes |= mode; };
		void	removeMode(ChannelModes mode) { _modes &= ~mode; };
		void	toggleMode(ChannelModes mode) { _modes ^= mode; };
		bool	isModeSet(ChannelModes mode) { return _modes & mode; };
};
