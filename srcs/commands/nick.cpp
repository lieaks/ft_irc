#include "../../includes/commands.hpp"

bool	cmd_nick(Client &client, std::vector<std::string> &input) {
	(void)client;
	(void)input;
	std::cout << "cmd_nick" << std::endl;
	return true;
}
