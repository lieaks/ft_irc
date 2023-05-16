#include "../../includes/commands.hpp"

bool	cmd_pass(Client &client, std::string &input) {
	(void)client;
	(void)input;
	std::cout << "cmd_pass" << std::endl;
	return true;
}
