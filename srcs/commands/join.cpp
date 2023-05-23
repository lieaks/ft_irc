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
	Channel *channel = server.getChannel(input[1]);
	if (channel == NULL)
	{
		channel = new Channel(input[1]);
		server.addChannel(channel);
	}
	client.joinChannel(channel);
	return true;
}
