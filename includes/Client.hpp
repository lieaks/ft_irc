#pragma once

#include <string>
#include <iostream>

class Client
{
private:
	int				_client_fd;
	std::string		_hostname;
	std::string		_input;
	
public:
	Client(int client_fd, std::string hostname);
	~Client() {};
	
	const std::string getInput() const;
	void setInput(std::string input);
};
