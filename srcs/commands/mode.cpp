#include "../../includes/commands.hpp"

ClientModes	get_mode_from_char(char c) {
	if (c == 'i')
		return INVISIBLE;
	if (c == 'w')
		return WALLOPS;
	if (c == 'o')
		return OPERATOR;
	return (ClientModes)0;
}

bool	change_user_mode(Server &server, Client &client, std::string &mode) {
	(void)server;
	bool	add_mode = true;

	for (size_t i = 0; i < mode.size(); i++) {
		if (mode[i] == '+') {
			add_mode = true;
			continue;
		}
		if (mode[i] == '-') {
			add_mode = false;
			continue;
		}
		if (get_mode_from_char(mode[i]) != 0) {
			if (add_mode)
				client.addMode(get_mode_from_char(mode[i]));
			else
				client.removeMode(get_mode_from_char(mode[i]));
			continue;
		}
		client.send_message(ERR_UMODEUNKNOWNFLAG(client.getNickname()));
		return false;
	}
	return true;
}

bool	cmd_mode(Server &server, Client &client, std::vector<std::string> &input) {
	if (input.size() < 3) {
		client.send_message(ERR_NEEDMOREPARAMS(client.getNickname(), "MODE"));
		return false;
	}
	if (input[2][0] != '#') {
		if (input[2] != client.getNickname()) {
			client.send_message(ERR_USERSDONTMATCH(client.getNickname()));
			return false;
		}
		return (change_user_mode(server, client, input[2]));
	}
	return true;
}
