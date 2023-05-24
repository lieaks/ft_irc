#include "../../includes/commands.hpp"

ClientModes	get_usermode_from_char(char c) {
	if (c == 'i')
		return INVISIBLE;
	if (c == 'w')
		return WALLOPS;
	if (c == 'o')
		return OPERATOR;
	return (ClientModes)0;
}

ChannelModes	get_channelmode_from_char(char c) {
	if (c == 'i')
		return INVITE_ONLY;
	if (c == 't')
		return TOPIC_PROTECTED;
	if (c == 'l')
		return LIMITED;
	if (c == 'k')
		return KEY;
	return (ChannelModes)0;
}

bool	change_user_mode(Client &client, std::string &mode) {
	bool		add_mode = true;
	std::string	message_to_send = "";
	for (size_t i = 0; i < mode.size(); i++) {
		if (mode[i] == '+') {
			add_mode = true;
			continue;
		}
		if (mode[i] == '-') {
			add_mode = false;
			continue;
		}
		if (mode[i] == 'o')
			continue;
		if (get_usermode_from_char(mode[i]) != 0) {
			if (add_mode)
				client.addMode(get_usermode_from_char(mode[i]));
			else
				client.removeMode(get_usermode_from_char(mode[i]));
			if (add_mode)
				message_to_send += "+";
			else
				message_to_send += "-";
			message_to_send += mode[i];
			continue;
		}
		client.send_message(ERR_UMODEUNKNOWNFLAG(client.getNickname()));
	}
	if (message_to_send != "")
		client.send_message(MODE_USER(client.getNickname(), client.getUsername(), client.getNickname(), message_to_send));
	return true;
}
// #define MODE_CHANNEL(nickname, username, channel, mode) (CLIENT_ID(nickname, username, "MODE") + "#" + channel + " " + mode + "\r\n")

// bool	change_channel_mode(Server &server, Channel &channel, std::string &mode) {
// 	bool		add_mode = true;
// 	std::string	message_to_send = "";
// 	for (size_t i = 0; i < mode.size(); i++) {
// 		if (mode[i] == '+') {
// 			add_mode = true;
// 			continue;
// 		}
// 		if (mode[i] == '-') {
// 			add_mode = false;
// 			continue;
// 		}
// 		if (mode[i] == 'o')
// 			continue;
// 		if (get_channelmode_from_char(mode[i]) != 0) {
// 			if (add_mode)
// 				channel.addMode(get_channelmode_from_char(mode[i]));
// 			else
// 				channel.removeMode(get_channelmode_from_char(mode[i]));
// 			if (add_mode)
// 				message_to_send += "+";
// 			else
// 				message_to_send += "-";
// 			message_to_send += mode[i];
// 			continue;
// 		}
// 		server.send_message_to_channel(channel, ERR_UMODEUNKNOWNFLAG(channel.getName()));
// 	}
// 	if (message_to_send != "")
// 		server.send_message_to_channel(channel, MODE_CHANNEL(channel.getName(), channel.getName(), channel.getName(), message_to_send));
// 	return true;
// }

bool	cmd_mode(Server &server, Client &client, std::vector<std::string> &input) {
	(void)server;
	if (client.isRegistered() == false && client.isAuth() == false)
	{
		client.send_message(ERR_NOTREGISTERED(client.getNickname(), "MODE"));
		return false;
	}
	if (input.size() < 3) {
		client.send_message(ERR_NEEDMOREPARAMS(client.getNickname(), "MODE"));
		return false;
	}
	if (input[2][0] != '#') {
		if (input[1] != client.getNickname()) {
			client.send_message(ERR_USERSDONTMATCH(client.getNickname()));
			return false;
		}
		return (change_user_mode(client, input[2]));
	} else {

	}
	return true;
}
