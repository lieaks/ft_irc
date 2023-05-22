#include "../../includes/commands.hpp"

bool	cmd_oper(Server &server, Client &client, std::vector<std::string> &input) {
	if (input.size() < 3) {
		client.send_message(ERR_NEEDMOREPARAMS(client.getNickname(), "INVITE"));
		return false;
	}
	Client	*target = server.getClient(input[1]);
	if (!target) {
		client.send_message(ERR_NOSUCHNICK(client.getNickname(), input[1]));
		return false;
	}
	if (server.getOperatorPassword() != input[2]) {
		client.send_message(ERR_PASSWDMISMATCH(client.getNickname()));
		return false;
	}
	target->send_message(RPL_YOUROPER(target->getNickname()));
	target->addMode(OPERATOR);
	return true;
}
