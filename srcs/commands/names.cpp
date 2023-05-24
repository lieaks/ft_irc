#include "../../includes/commands.hpp"

bool	cmd_names(Server &server, Client &client, std::vector<std::string> &input)
{
	if (input.size() < 2)
	{
		client.send_message(server.getNamesClients());
		return true;
	}
	else
	{
		std::string name_clients;
		std::vector<std::string> channel_name = split(input[1], ",");
		for (std::vector<std::string>::iterator it = channel_name.begin();\
			it != channel_name.end(); it++)
		{
			Channel	*channel = server.getChannelByName(it->substr(1));
			if (!channel) {
				client.send_message(ERR_NOSUCHCHANNEL(client.getNickname(), *it));
				continue;
			}
			name_clients = channel->getNamesClients();
			client.send_message(RPL_NAMREPLY(client.getNickname(), *it, name_clients));
			client.send_message(RPL_ENDOFNAMES(client.getNickname(), *it));
		}
	}
	return true;
}
