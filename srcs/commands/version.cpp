#include "../../includes/commands.hpp"


bool	cmd_version(Server &server, Client &client, std::vector<std::string> &input)
{
	if (input.size() > 1 && input[1] != SERVER_NAME)
	{
		client.send_message(ERR_NOSUCHSERVER(client.getNickname()));
		return false;
	}
	client.send_message(RPL_VERSION(client.getNickname()));
	return true;
};
