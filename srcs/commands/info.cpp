#include "../../includes/commands.hpp"

/*
     Command: INFO
  Parameters: None

*/
bool	cmd_info(Server &server, Client &client, std::vector<std::string> &input) 
{
	if (input.size() > 1 && input[1] != SERVER_NAME)
	{
		client.send_message(ERR_NOSUCHSERVER(client.getNickname()));
		return false;
	}
	client.send_message(RPL_INFO(client.getNickname()));
	client.send_message(RPL_ENDOFINFO(client.getNickname()));
	return true;
}
