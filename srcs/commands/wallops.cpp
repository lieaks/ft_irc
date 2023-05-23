#include "../../includes/commands.hpp"

bool	cmd_wallops(Server &server, Client &client, std::vector<std::string> &input) {
	if (client.isRegistered() == false && client.isAuth() == false)
	{
		client.send_message(ERR_NOTREGISTERED(client.getNickname(), "WALLOPS"));
		return false;
	}
	if (input.size() < 2) {
		client.send_message(ERR_NEEDMOREPARAMS(client.getNickname(), "WALLOPS"));
		return false;
	}
	if (!client.isModeSet(OPERATOR)) {
		client.send_message(ERR_NOPRIVILEGES(client.getNickname()));
		return false;
	}
	std::map<int, Client *>::iterator it = server.getClients().begin();
	std::string	full_msg;

	for (size_t i = 1; i < input.size(); i++) {
		full_msg += input[i];
		if (i + 1 < input.size())
			full_msg += " ";
	}
	if (full_msg[0] == ':')
		full_msg.erase(0, 1);
	while (it != server.getClients().end()) {
		if (it->second->isModeSet(WALLOPS)) {
			it->second->send_message(":" + client.getNickname() + " WALLOPS :" + full_msg + "\r\n");
		}
		++it;
	}
	return true;
}
