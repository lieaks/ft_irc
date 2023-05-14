#include <iostream>
#include <sstream>
#include "../includes/Server.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
		return (std::cerr << "Usage: ./ircserv <port> <password>" << std::endl, 1);

	int port = 0;
	std::stringstream(av[1]) >> port;
	std::cout << "port: " << port << std::endl;

	try {
		Server irc(port, av[2]);
		irc.run_server();
	}
	catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
};
