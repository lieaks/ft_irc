#include "../../includes/commands.hpp"

bool	cmd_join(Server &server, Client &client, std::vector<std::string> &input) {
	(void)server;
	if (input.size() < 2)
	{
		client.send_message(ERR_NEEDMOREPARAMS(client.getNickname(), input[0]));
		return false;
	}
	if (client.isRegistered() == false)
	{
		client.send_message(ERR_NOTREGISTERED(client.getNickname(), input[0]));
		return false;
	}
	if (input[1][0] == '#')
		input[1] = input[1].substr(1);
	Channel *channel = server.getChannelByName(input[1]);
	if (channel == NULL)
	{
		channel = new Channel(input[1], "", &client);
		server.addChannel(channel);
	}
	client.joinChannel(channel);
	channel->send_message(JOIN(client.getNickname(), client.getUsername(), channel->getName()));
	if (channel->getTopic() != "")
		client.send_message(RPL_TOPIC(client.getNickname(), channel->getName(), channel->getTopic()));
	else
		client.send_message(RPL_NOTOPIC(client.getNickname(), channel->getName()));
	// client.send_message(RPL_NAMREPLY(client.getNickname(), channel->getName(), channel->getNamesClients()));
	// client.send_message(RPL_ENDOFNAMES(client.getNickname(), channel->getName()));
	return true;
}
