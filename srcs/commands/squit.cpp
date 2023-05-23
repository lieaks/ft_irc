#include "../../includes/commands.hpp"

bool	cmd_squit(Server &server, Client &client, std::vector<std::string> &input) {
	(void)input;
	if (!client.isModeSet(OPERATOR)) {
		client.send_message(ERR_NOPRIVILEGES(":Permission Denied- You're not an IRC operator"));
		return false;
	}
	server.setRunning(false);
	return true;
}
