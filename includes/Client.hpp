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

	public:
		Client(int client_fd, std::string hostname);
		~Client() {};

		const std::string	getInput() const;
		void				clearInput();
		void				setInput(std::string input);
};
