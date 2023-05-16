#include "../../includes/commands.hpp"

bool	cmd_user(Server &server, Client &client, std::vector<std::string> &input) {
	(void)server;
	(void)client;
	(void)input;
	std::cout << "cmd_user" << std::endl;
	return true;
}
