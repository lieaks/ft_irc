#include "../../includes/commands.hpp"
/*
      Command: VERSION
   Parameters: [ <target> ]

   The VERSION command is used to query the version of the server
   program.  An optional parameter <target> is used to query the version
   of the server program which a client is not directly connected to.

   Numeric Replies:

           ERR_NOSUCHSERVER                RPL_VERSION
*/

bool	cmd_version(Server &server, Client &client, std::vector<std::string> &input)
{
	(void)server;
	if (input.size() > 1 && input[1] != SERVER_NAME)
	{
		client.send_message(ERR_NOSUCHSERVER(client.getNickname()));
		return false;
	}
	client.send_message(RPL_VERSION(client.getNickname()));
	return true;
};
