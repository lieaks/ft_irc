#include "../../includes/commands.hpp"

bool	cmd_privmsg(Server &server, Client &client, std::vector<std::string> &input)
{
	if (input.size() < 2 || input.size() == 2 && input[1][0] != ':')
	{
		client.send_message(ERR_NEEDMOREPARAMS(client.getNickname(), input[0]));
		return false;
	}
	if (not input[1].empty() && input[1][0] == ':')
	{
		client.send_message(ERR_NO)
		return false;
	}
	return true;
}
