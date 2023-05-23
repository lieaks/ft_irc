#include "../../includes/commands.hpp"

bool	cmd_quit(Server &server, Client &client, std::vector<std::string> &input) {
	for (std::vector<Channel *>::iterator channels = client.getChannels().begin(); channels != client.getChannels().end(); channels++) {
		(*channels)->send_message(NOTICE(client.getNickname(), client.getHostname(), "QUIT", input[1].substr(1)));
	}
	server.removeClient(server.getClientByNick(client.getNickname()));
	return true;
}
