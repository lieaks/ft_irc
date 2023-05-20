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
	if (target->isModeSet(OPERATOR)) {
		client.send_message(ERR_ALREADYREGISTRED(client.getNickname()));
		return false;
	}
	if (server.getOperatorPassword() != input[2]) {
		client.send_message(ERR_PASSWDMISMATCH(client.getNickname()));
		return false;
	}
	target->addMode(OPERATOR);
	return true;
}
