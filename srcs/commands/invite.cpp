#include "../../includes/commands.hpp"

bool	cmd_invite(Server &server, Client &client, std::vector<std::string> &input) {
	if (input.size() < 2) {
		client.send_message(ERR_NEEDMOREPARAMS(client.getNickname(), "INVITE"));
		return false;
	}
	Client	*target = server.getClient(input[1]);
	if (!target) {
		client.send_message(ERR_NOSUCHNICK(client.getNickname(), input[1]));
		return false;
	}
	target->send_message(RPL_INVITING(client.getNickname(), target->getNickname(), input[2]));
	Channel	*channel = server.getChannel(input[2]);
	if (channel) {
		channel->addInvitation(target);
	}
	return true;
}
