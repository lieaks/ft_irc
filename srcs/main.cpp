#include <iostream>
#include <sstream>
#include "../includes/Server.hpp"

int main(int ac, char **av)
{
	(void)av;
	std::stringstream ss;
	int port = 0;
	if (ac != 3)
	{
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return 1;
	};
	ss << av[1];
	ss >> port;
	Server irc(port, av[2]);
};
