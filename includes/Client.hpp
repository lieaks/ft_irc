#pragma once

#include <string>
#include <iostream>
#include <vector>

class Client
{
	private:
		int				_client_fd;
		std::string		_hostname;
		std::string		_input;
		std::string		_nickname;

	public:
		Client(int client_fd, std::string hostname);
		~Client() {};

		// Getters and setters
		const	std::string	getInput() const;
		const	std::string	&getNickname() const { return _nickname; };

		void				setInput(std::string input);
		void				setNickname( std::string const &nickname ) { _nickname = nickname; };
		
		void				clearInput();
};
