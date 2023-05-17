#include "../../includes/commands.hpp"

bool	cmd_pass(Server &server, Client &client, std::vector<std::string> &input) {
	(void)server;
	(void)client;
	(void)input;
	if (input.empty() || input[0].empty()){
		client.send_message(ERR_NEEDMOREPARAMS(client.getNickname(), input[0]));
		return false;
		}
	else if (client.getPassword()) {
		client.send_message(ERR_ALREADYREGISTRED(client.getNickname()));
		return false;
		}
	else if (not client.getPassword() && server.getPassword() == input[0])
		client.setPassword(true);
	std::cout << "cmd_pass" << std::endl;
	return true;
}
