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
		client.send_message(ERR_NOTREGISTERED(client.getNickname()));
		return false;
	}
	return true;
}
