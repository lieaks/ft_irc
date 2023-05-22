#include "../../includes/commands.hpp"

bool	cmd_quit(Server &server, Client &client, std::vector<std::string> &input) {
	(void)input;
	std::vector<Channel *>::iterator channels = client.getChannels().begin();
	while (channels != client.getChannels().end()) {
		(*channels)->send_message(NOTICE(client.getNickname(), client.getHostname(), "QUIT", input[2]));
	}
	server.removeClient(server.getClient(client.getNickname()));
	return true;
}
