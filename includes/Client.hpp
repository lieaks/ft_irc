#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Channel.hpp"
#include <sys/socket.h> // send

class Channel;

class Client
{
	private:
		int						_client_fd;
		std::string				_hostname;
		std::string				_input;
		std::string				_nickname;
		Channel					*_active_channel;
		std::vector<Channel *>	_channels;

	public:
		Client(int client_fd, std::string hostname);
		~Client();

		// Getters and setters
		const std::string	getInput() const { return _input; };
		const std::string	getNickname() const { return _nickname; };
		int					getFd() const { return _client_fd; };
		std::vector<Channel *>&	getChannels() { return _channels; };
		Channel			*getActiveChannel() const { return _active_channel; };
		Channel			*getChannel(std::string const channel_name);

		void				setActiveChannel(Channel *channel) { _active_channel = channel; };
		void				setInput(std::string input) { _input = input; };
		void				setNickname( std::string const &nickname ) { _nickname = nickname; };
		
		void				clearInput() { _input.clear(); };

		// channel related
		bool				joinChannel(Channel *channel);
		void				leaveChannel(Channel *channel);
		void				leaveAllChannels();
		void				leaveActiveChannel();

		// socket related
		void				send_message(const std::string message);
};
