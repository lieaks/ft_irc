#include "../../includes/commands.hpp"

bool	cmd_part(Server &server, Client &client, std::vector<std::string> &input) {
	if (client.isRegistered() == false && client.isAuth() == false)
	{
		client.send_message(ERR_NOTREGISTERED(client.getNickname(), "PART"));
		return false;
	}
	if (input.size() < 2) {
		client.send_message(ERR_NEEDMOREPARAMS(client.getNickname(), "PART"));
		return false;
	}
	if (input.size() == 2)
		input.push_back("");
	std::vector<std::string> channels = split(input[1], ",");
	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++) {
		if (server.getChannelByName((*it).substr(1)) == NULL) {
			client.send_message(ERR_NOSUCHCHANNEL(client.getNickname(), *it));
			continue;
		}
		Channel	*channel = client.getChannel((*it).substr(1));
		if (!channel) {
			client.send_message(ERR_NOTONCHANNEL(client.getNickname(), *it));
			continue;
		}
		channel->send_message(PART(client.getNickname(), client.getUsername(), channel->getName(), input[2]));
		client.leaveChannel(channel);
	}
	return true;
}
