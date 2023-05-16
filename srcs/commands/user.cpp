#include "../../includes/commands.hpp"

bool	cmd_user(Client &client, std::vector<std::string> &input) {
	(void)client;
	(void)input;
	std::cout << "cmd_user" << std::endl;
	return true;
}
