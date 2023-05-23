#include "../../includes/commands.hpp"

bool	cmd_quit(Server &server, Client &client, std::vector<std::string> &input) {
	std::vector<Channel *>::iterator channels = client.getChannels().begin();
	std::cout << "in quit. client's channels len: " << client.getChannels().size() << std::endl;
	while (channels != client.getChannels().end()) {
		std::cout << "quitting message: " + NOTICE(client.getNickname(), client.getHostname(), "QUIT", input[1].substr(1));
		(*channels)->send_message(NOTICE(client.getNickname(), client.getHostname(), "QUIT", input[1].substr(1)));
		channels++;
	}
	server.removeClient(server.getClient(client.getNickname()));
	return true;
}
