#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Channel.hpp"
#include <sys/socket.h> // send

class Channel;

enum ClientModes {
	AWAY = 1 << 0,
	INVISIBLE = 1 << 1,
	WALLOPS = 1 << 2,
	RESTRICTED = 1 << 3,
	OPERATOR = 1 << 4,
	LOCAL_OPERATOR = 1 << 5,
	RECEIVE_SERVER_NOTICES = 1 << 6,
};

class Client
{
	private:
		int						_client_fd;
		std::string				_hostname;
		std::string				_input;
		std::string				_nickname;
		bool					_isAuth;
		std::string				_realname;
		Channel					*_active_channel;
		std::vector<Channel *>	_channels;
		int						_modes;

	public:
		Client(int client_fd, std::string hostname);
		~Client();

		// Getters and setters
		const std::string	getInput() const { return _input; };
		const std::string	getNickname() const { return _nickname; };
		const std::string	getRealname() const { return _realname; };
		int					getFd() const { return _client_fd; };
		std::vector<Channel *>&	getChannels() { return _channels; };
		Channel				*getActiveChannel() const { return _active_channel; };
		Channel				*getChannel(std::string const channel_name);
		const bool			isAuth() const { return _isAuth; }

		void				setActiveChannel(Channel *channel) { _active_channel = channel; };
		void				setInput(std::string input) { _input = input; };
		void				setNickname(std::string const &nickname ) { _nickname = nickname; };
		void				setRealname( std::string const &realname ) { _realname = realname; };
		void				setAuth(bool isAuth) { _isAuth = isAuth; };
		int					&getModes() { return _modes; };

		void				clearInput() { _input.clear(); };

		// channel related
		bool				joinChannel(Channel *channel);
		void				leaveChannel(Channel *channel);
		void				leaveAllChannels();
		void				leaveActiveChannel();

		// socket related
		void				send_message(const std::string message);

		// modes related
		void	addMode(ClientModes mode) { _modes |= mode; };
		void	removeMode(ClientModes mode) { _modes &= ~mode; };
		void	toggleMode(ClientModes mode) { _modes ^= mode; };
		bool	isModeSet(ClientModes mode) { return _modes & mode; };
};
