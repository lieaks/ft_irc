#include "../../includes/commands.hpp"

extern bool g_running;

bool	cmd_die(Server &server, Client &client, std::vector<std::string> &input) {
	(void)server;
	(void)input;
	if (client.isRegistered() == false && client.isAuth() == false)
	{
		client.send_message(ERR_NOTREGISTERED(client.getNickname(), "IE"));
		return false;
	}
	if (!client.isModeSet(OPERATOR)) {
		client.send_message(ERR_NOPRIVILEGES(client.getNickname()));
		return false;
	}
	g_running = false;
	return true;
}
