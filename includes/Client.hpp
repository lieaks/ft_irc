#pragma once

#include <string>
#include <iostream>

class Client
{
private:
	int				_client_fd;
	std::string		_hostname;
	
public:
	Client(int client_fd, std::string hostname);
	~Client() {};
};
