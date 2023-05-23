#include "../../includes/commands.hpp"

bool	cmd_squit(Server &server, Client &client, std::vector<std::string> &input) {
	(void)input;
	if (!client.isModeSet(OPERATOR)) {
		client.send_message(ERR_NOPRIVILEGES(client.getNickname()));
		return false;
	}
	server.setRunning(false);
	return true;
}
