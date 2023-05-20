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
	// TODO: use input[2] as password
	return true;
}
