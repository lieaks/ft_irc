#include "../../includes/commands.hpp"

bool	cmd_invite(Server &server, Client &client, std::vector<std::string> &input) {
	if (input.size() < 3) {
		client.send_message(ERR_NEEDMOREPARAMS(client.getNickname(), "INVITE"));
		return false;
	}
	if (input[2][0] == '#')
		input[2] = input[2].substr(1);
	if (!client.getChannel(input[2])) {
		client.send_message(ERR_NOTONCHANNEL(client.getNickname(), input[2]));
		return false;
	}
	Client	*target = server.getClientByNick(input[1]);
	if (!target) {
		client.send_message(ERR_NOSUCHNICK(client.getNickname(), input[1]));
		return false;
	}
	if (target->getChannel(input[2])) {
		client.send_message(ERR_USERONCHANNEL(client.getNickname(), input[2], input[1]));
		return false;
	}
	client.send_message(RPL_INVITING(client.getNickname(), target->getNickname(), input[2]));
	target->send_message(INVITE(client.getNickname(), client.getUsername(), input[1], input[2]));
	Channel	*channel = server.getChannelByName(input[2]);
	if (channel) {
		channel->addInvitation(target);
	}
	return true;
}
