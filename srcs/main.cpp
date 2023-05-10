#include <string>
#include <iostream>

int main(int ac, char **av)
{
	(void)av;
	if (ac != 3)
	{
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return 1;
	}		
};
