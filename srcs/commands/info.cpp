#include "../../includes/commands.hpp"

/*
        Command: INFO
   Parameters: [ <target> ]

   The INFO command is REQUIRED to return information describing the
   server: its version, when it was compiled, the patchlevel, when it
   was started, and any other miscellaneous information which may be
   considered to be relevant.

   Numeric Replies:

           ERR_NOSUCHSERVER
           RPL_INFO                      RPL_ENDOFINFO

*/
bool	cmd_info(Server &server, Client &client, std::vector<std::string> &input) 
{
	(void)server;
	if (input.size() > 1 && input[1] != SERVER_NAME)
	{
		client.send_message(ERR_NOSUCHSERVER(client.getNickname()));
		return false;
	}
	client.send_message(RPL_INFO(client.getNickname()));
	client.send_message(RPL_ENDOFINFO(client.getNickname()));
	return true;
}
