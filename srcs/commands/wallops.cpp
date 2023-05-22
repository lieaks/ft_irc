#include "../../includes/commands.hpp"

bool	cmd_wallops(Server &server, Client &client, std::vector<std::string> &input) {
	if (input.size() < 2) {
		client.send_message(ERR_NEEDMOREPARAMS(client.getNickname(), "WALLOPS"));
		return false;
	}
	if (!client.isModeSet(OPERATOR)) {
		client.send_message(ERR_NOPRIVILEGES(client.getNickname()));
		return false;
	}
	std::map<int, Client *>::iterator it = server.getClients().begin();
	while (it != server.getClients().end()) {
		if (it->second->isModeSet(WALLOPS)) {
			it->second->send_message(":" + client.getNickname() + " WALLOPS :" + input[1]);
			std::cout << "Hello world !" << std::endl;
		}
		++it;
	}
	return true;
}
