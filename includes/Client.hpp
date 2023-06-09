#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Channel.hpp"
#include <sys/socket.h> // send

class Channel;

enum ClientModes {
	INVISIBLE = 1 << 1,
	WALLOPS = 1 << 2,
	/* AWAY = 1 << 3, */
	OPERATOR = 1 << 4,
};

class Client
{
	private:
		int						_client_fd;
		std::string				_hostname;
		std::string				_input;
		std::string				_nickname;
		std::string				_username;
		std::string				_realname;
		Channel					*_active_channel;
		std::vector<Channel *>	_channels;
		int						_modes;
		bool					_isRegistered;
		bool					_isAuth;

	public:
		Client(int client_fd, std::string hostname);
		~Client();

		// Getters and setters
		const std::string		getInput() const { return _input; };
		const std::string		getHostname() const { return _hostname; };
		const std::string		getNickname() const { return _nickname; };
		const std::string		getUsername() const { return _username; };
		const std::string		getRealname() const { return _realname; };
		int						getFd() const { return _client_fd; };
		std::vector<Channel *>&	getChannels() { return _channels; };
		Channel					*getActiveChannel() const { return _active_channel; };
		Channel					*getChannel(std::string const channel_name);
		bool					isRegistered() const { return _isRegistered; }
		bool					isAuth() const { return _isAuth; }

		void				setActiveChannel(Channel *channel) { _active_channel = channel; };
		void				setInput(std::string input) { _input = input; };
		void				setNickname(std::string const &nickname ) { _nickname = nickname; };
		void				setUsername(std::string const &username ) { _username = username; };
		void				setRealname( std::string const &realname ) { _realname = realname; };
		void				setRegistered(bool isRegistered) { _isRegistered = isRegistered; };
		void				setAuth(bool isAuth) { _isAuth = isAuth; };
		int					&getModes() { return _modes; };

		void				clearInput() { _input.clear(); };

		void				send_message(const std::string message);

		// channel related
		void				joinChannel(Channel *channel);
		void				leaveChannel(Channel *channel);
		void				leaveAllChannels();
		void				leaveActiveChannel();

		// modes related
		void	addMode(ClientModes mode) { _modes |= mode; };
		void	removeMode(ClientModes mode) { _modes &= ~mode; };
		void	toggleMode(ClientModes mode) { _modes ^= mode; };
		bool	isModeSet(ClientModes mode) { return _modes & mode; };
};
