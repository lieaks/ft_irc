#include "../../includes/commands.hpp"

bool	cmd_names(Server &server, Client &client, std::vector<std::string> &input)
{
	(void)server;
	(void)client;
	(void)input;
	if (input.size() < 2)
	{
		client.send_message(server.getNamesClients());
		return true;
	}
	else
	{
		Channel *channel;
		std::string name_clients;
		std::vector<std::string> channel_name = split(input[1], ",");
		for (std::vector<std::string>::iterator it = channel_name.begin();\
			it != channel_name.end(); it++)
		{
			name_clients = server.getChannelByName(it->substr(1, it->size() - 1))->getNamesClients();
			client.send_message(RPL_NAMREPLY(client.getNickname(), *it, name_clients));
			client.send_message(RPL_ENDOFNAMES(client.getNickname(), *it));
		}
	}
	return true;
}
