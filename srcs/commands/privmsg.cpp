#include "../../includes/commands.hpp"

bool	cmd_privmsg(Server &server, Client &client, std::vector<std::string> &input)
{
	(void)server;
	if (input.size() < 2 || (input.size() == 2 && input[1][0] != ':'))
	{
		client.send_message(ERR_NEEDMOREPARAMS(client.getNickname(), input[0]));
		return false;
	}
	if (not input[1].empty() && input[1][0] == ':')
	{
		client.send_message(ERR_NORECIPIENT(client.getNickname(), input[0]));
		return false;
	}
	std::string msg = join(input, " ", 2);
	msg = msg.substr(2, msg.length() - 1);
	if (msg.empty())
	{
		client.send_message(ERR_NOTEXTTOSEND(client.getNickname()));
		return false;
	}
	return true;
}
