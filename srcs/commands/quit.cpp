#include "../../includes/commands.hpp"

bool	cmd_quit(Server &server, Client &client, std::vector<std::string> &input) {
	(void)input;
	std::vector<Channel *>::iterator channels = client.getChannels().begin();
	while (channels != client.getChannels().end()) {
		/* TODO: send notice to channels users about the user quitting */
		(*channels)->send_message(RPL_NOTICE(client.getNickname(), input[1]));
	}
	server.removeClient(server.getClient(client.getNickname()));
	return true;
}
