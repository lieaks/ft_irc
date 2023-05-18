#include "../../includes/commands.hpp"

bool	cmd_ping(Server &server, Client &client, std::vector<std::string> &input)
{
	if (input.empty()) {
		client.send_message(ERR_NOORIGIN(client.getNickname()));
		return false;
	}
	client.send_message(PONG(client.getNickname()));
	return true;
}
