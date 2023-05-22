#include "../../includes/commands.hpp"

bool	parse_nick(std::string &nickname) {
	if (nickname.size() > 9) {
		// std::cerr << "[NICK] Error: nickname too long" << std::endl;
		return false;
	}
	if (nickname.find_first_not_of(NICK_VALID_CHARS) != std::string::npos) {
		// std::cerr << "[NICK] Error: invalid nickname" << std::endl;
		return false;
	}
	return true;
}

bool	is_nick_taken(Server &server, std::string &nickname) {
	for (std::map<int, Client*>::iterator it = server.getClients().begin();
			it != server.getClients().end(); it++) {
		if (it->second->getNickname() == nickname) {
			// std::cerr << "[NICK] Error: nickname already taken" << std::endl;
			return true;
		}
	}
	return false;
}

bool	cmd_nick(Server &server, Client &client, std::vector<std::string> &input) {
	if (input.size() < 2) {
		// std::cerr << "[NICK] Error: not enough arguments" << std::endl;
		client.send_message(ERR_NEEDMOREPARAMS(client.getNickname(), "NICK"));
		return false;
	}
	if (client.getNickname() == input[1]) {
		return true;
	}
	// std::cout << "Nickname: " << input[1] << "\"" << std::endl;
	if (!parse_nick(input[1])) {
		// TODO: send ERR_ERRONEUSNICKNAME
		client.send_message(ERR_ERRONEUSNICKNAME(input[1]));
		return false;
	}
	if (is_nick_taken(server, input[1])) {
		// TODO: send ERR_NICKNAMEINUSE
		client.send_message(ERR_NICKNAMEINUSE(input[1]));
		return false;
	}
	// if (is_nick_collision(server, input[1])) {
	// 	TODO: send ERR_NICKCOLLISION
	// 	return false;
	// }
	client.send_message(NICK(client.getNickname(), client.getHostname(), input[1]));
	client.setNickname(input[1]);
	// std::cout << "New nickname: " << client.getNickname() << std::endl;
	return true;
}
