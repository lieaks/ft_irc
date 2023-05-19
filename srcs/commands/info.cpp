#include "../../includes/commands.hpp"

bool	cmd_info(Server &server, Client &client, std::vector<std::string> &input) 
{
	client.send_message(RPL_INFO(client.getNickname()));
	client.send_message(RPL_ENDOFINFO(client.getNickname()));
	return true;
}
