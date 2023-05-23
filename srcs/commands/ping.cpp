#include "../../includes/commands.hpp"

bool	cmd_ping(Server &server, Client &client, std::vector<std::string> &input)
{
	if (client.isRegistered() == false && client.isAuth() == false)
	{
		client.send_message(ERR_NOTREGISTERED(client.getNickname(), "PING"));
		return false;
	}
	(void)server;
	if (input.size() < 2) {
		client.send_message(ERR_NOORIGIN(client.getNickname()));
		return false;
	}
	if (input[1] != SERVER_NAME) {
		client.send_message(ERR_NOSUCHSERVER(client.getNickname()));
		return false;
	}
	client.send_message(PONG(client.getNickname()));
	return true;
}
