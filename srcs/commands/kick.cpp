#include "../../includes/commands.hpp"

bool	cmd_kick(Server &server, Client &client, std::vector<std::string> &input) {
	if (client.isRegistered() == false && client.isAuth() == false)
	{
		client.send_message(ERR_NOTREGISTERED(client.getNickname(), "KICK"));
		return false;
	}
	if (input.size() < 3) {
		client.send_message(ERR_NEEDMOREPARAMS(client.getNickname(), "KICK"));
		return false;
	}
	Channel *channel = server.getChannelByName(input[1].substr(1));
	if (!channel) {
		client.send_message(ERR_NOSUCHCHANNEL(client.getNickname(), input[1]));
		return false;
	}
	if (client.getChannel(input[1].substr(1)) == NULL) {
		client.send_message(ERR_NOTONCHANNEL(client.getNickname(), input[1]));
		return false;
	}
	Client *target = channel->getClientByNick(input[2]);
	if (!target) {
		client.send_message(ERR_USERNOTINCHANNEL(client.getNickname(), channel->getName(), input[2]));
		return false;
	}
	if (!(client.isModeSet(OPERATOR) || channel->isOperator(&client) || channel->getCreator() == &client)) {
		client.send_message(ERR_CHANOPRIVSNEEDED(client.getNickname(), channel->getName()));
		return false;
	}
	if (input.size() == 3) {}
		input.push_back("");
	channel->send_message(KICK(client.getNickname(), client.getUsername(), channel->getName(), target->getNickname(), input[3]));
	target->leaveChannel(channel);
	return true;
}
