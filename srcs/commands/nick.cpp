#include "../../includes/commands.hpp"

bool	cmd_nick(Client &client, std::vector<std::string> &input) {
	client.setNickname(input[1]);
	std::cout << "New nickname: " << client.getNickname() << std::endl;
	return true;
}
