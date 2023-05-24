#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include "../includes/Server.hpp"
#include <fstream>
#include <string>
#include <csignal>

bool	g_running = true;

void signalHandler(int signum)
{
	if (signum == SIGINT)
		g_running = false;
}

int main(int ac, char **av)
{
	signal(SIGINT, signalHandler);
	if (ac != 3)
		return (std::cerr << "Usage: ./ircserv <port> <password>" << std::endl, 1);

	char *ptr;
	errno = 0;
	long port = std::strtol(av[1], &ptr, 10);
	if (ptr != av[1] + std::strlen(av[1]) || std::strlen(av[1]) == 0)
		return (std::cerr << "Error: Invalid port \"" << av[1] << "\": not a number" << std::endl, 1);
	else if (errno != 0)
		return (std::cerr << "Error: Invalid port \"" << av[1] << "\": " << strerror(errno) << std::endl, 1);
	else if (port < 0 || port > 65535)
		return (std::cerr << "Error: Invalid port \"" << av[1] << "\": must be between 0 and 65535" << std::endl, 1);

	std::ifstream	env_file(".env");
	std::string password;
	env_file >> password;

	try {
		// std::cout << "port: " << port << std::endl;
		Server irc(port, av[2], password);
		irc.run_server();
	}
	catch (const std::exception &e) {
		std::cerr << e.what();
		if (errno != 0)
			std::cerr << ": " << strerror(errno);
		std::cerr << std::endl; 
	}
};
