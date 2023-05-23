#include "../../includes/commands.hpp"

bool	client_privmsg(Server &server, Client &client, std::string msg, std::string dest)
{
	Client* dest_client = server.getClientByNick(dest);
	if (dest_client == NULL)
	{
		client.send_message(ERR_NOSUCHNICK(client.getNickname(), dest));
		return false;
	}
	dest_client->send_message(PRIVMSG(client.getNickname(), client.getHostname() ,dest, msg));
	return true;
}

bool	channel_privmsg(Server &server, Client &client, std::string msg, std::string dest)
{
	Channel* channel = server.getChannelByName(dest.substr(1, dest.length() - 1));
	if (channel == NULL)
	{
		client.send_message(ERR_NOSUCHNICK(client.getNickname(), dest));
		return false;
	}
	channel->send_message(PRIVMSG(client.getNickname(), client.getHostname(), "#" + dest, msg));
	return true;
}

bool	cmd_privmsg(Server &server, Client &client, std::vector<std::string> &input)
{
	(void)server;
	if (input.size() < 3  || (input.size() == 2 && input.at(0)[1] != ':'))
	{
		client.send_message(ERR_NEEDMOREPARAMS(client.getNickname(), input[0]));
		return false;
	}
	if (not input[1].empty() && input.at(0)[1] == ':')
	{
		client.send_message(ERR_NORECIPIENT(client.getNickname(), input[0]));
		return false;
	}
	std::string msg = join(input, " ", 2);
	msg = msg.substr(1, msg.length() - 1);
	if (msg.empty())
	{
		client.send_message(ERR_NOTEXTTOSEND(client.getNickname()));
		return false;
	}
	if (input.at(1)[0] == '#')
	{
		channel_privmsg(server, client, msg, input[1]);
	}
	else
		client_privmsg(server, client, msg, input[1]);
	return true;
}
