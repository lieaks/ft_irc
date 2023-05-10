#include <string>
#include <iostream>

int main(int ac, char **av)
{
	(void)av;
	if (ac != 3)
	{
		std::cerr << "Usage: ./irc <port> <username" << std::endl;
		return 1;
	}		
};
