#include "../../includes/commands.hpp"

bool	cmd_join(Server &server, Client &client, std::vector<std::string> &input) {
	(void)server;
	if (client.isRegistered() == false && client.isAuth() == false)
	{
		client.send_message(ERR_NOTREGISTERED(client.getNickname(), "JOIN"));
		return false;
	}
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
	Channel *channel = server.getChannelByName(input[1].substr(1));
	if (channel == NULL)
	{
		channel = new Channel(input[1].substr(1), server, &client);
		server.addChannel(channel);
	}
	else
	{
		if (not channel->getKey().empty() && (input.size() < 3 || input[2] != channel->getKey()))
		{
			client.send_message(ERR_BADCHANNELKEY(client.getNickname(), channel->getName()));
			return false;
		}
		if (channel->isModeSet(INVITE_ONLY) && not channel->isInvited(&client))
		{
			client.send_message(ERR_INVITEONLYCHAN(client.getNickname(), channel->getName()));
			return false;
		}
		if (channel->isModeSet(LIMITED) && channel->getClients().size() == channel->getLimit())
		{
			client.send_message(ERR_CHANNELISFULL(client.getNickname(), channel->getName()));
			return false;
		}
	}
	client.joinChannel(channel);
	channel->send_message(JOIN(client.getNickname(), client.getUsername(), channel->getName()));
	channel->removeInvitation(&client);
	cmd_topic(server, client, input);
	cmd_names(server, client, input);
	return true;
}
