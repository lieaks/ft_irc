#include "../../includes/commands.hpp"

bool	cmd_pass(Server &server, Client &client, std::vector<std::string> &input) {
	if (input.size() < 2 || input[0].empty()){
		client.send_message(ERR_NEEDMOREPARAMS(client.getNickname(), input[0]));
		return false;
	}
	else if (client.isAuth()) {
		client.send_message(ERR_ALREADYREGISTRED(client.getNickname()));
		return false;
	}
	else if (not client.isAuth() && server.getPassword() == input[0])
		client.setAuth(true);
	std::cout << "cmd_pass" << std::endl;
	return true;
}
