#include "../../includes/commands.hpp"

bool	cmd_pass(Server &server, Client &client, std::vector<std::string> &input) {
	(void)server;
	(void)client;
	(void)input;
	std::cout << "cmd_pass" << std::endl;
	return true;
}
