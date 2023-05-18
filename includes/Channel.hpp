#pragma once

#include "Client.hpp"
#include <string>
#include <vector>
#include <algorithm>

class Client;

enum ChannelModes {
	NONE = 0,
	/* OPERATOR_PRIV = 1 << 0, */ // useless, we use the operator list
	PRIVATE = 1 << 1,
	SECRET = 1 << 2,
	INVITE_ONLY = 1 << 3,
	TOPIC_PROTECTED = 1 << 4,
	NO_MESSAGES = 1 << 5,
	MODERATED = 1 << 6,
	LIMITED = 1 << 7,
	BAN_MASK = 1 << 8,
	VOICE = 1 << 9,
	KEY = 1 << 10,
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
		std::vector<Client *>	_banned;
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
		Client				*getCreator() { return _creator; };
		int					&getMode() { return _modes; };
		time_t				getCreationDate() const { return _created_at; };
		size_t				getLimit() const { return _limit; };

		void	setName(const std::string name) { _name = name; };
		void	setTopic(const std::string topic) { _topic = topic; };
		void	setKey(const std::string key) { _key = key; };
		void	setLimit(size_t limit) { _limit = limit; };
		void	setCreator(Client *creator) { _creator = creator; };

		// clients related
		bool	addClient(Client *client);
		void	removeClient(Client *client);
		void	send_message(const std::string message);
		void	addOperator(Client *client);
		void	removeOperator(Client *client);
		bool	isOperator(Client *client);

		// modes related
		void	addMode(ChannelModes mode) { _modes |= mode; };
		void	removeMode(ChannelModes mode) { _modes &= ~mode; };
		void	toggleMode(ChannelModes mode) { _modes ^= mode; };
		bool	isModeSet(ChannelModes mode) { return _modes & mode; };

		// ban mask
		void	addBan(Client *client);
		void	removeBan(Client *client);
		bool	isBanned(Client *client);
};
