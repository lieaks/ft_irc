#include "../../includes/commands.hpp"
/*
      Command: TIME
   Parameters: [ <target> ]

   The time command is used to query local time from the specified
   server. If the <target> parameter is not given, the server receiving
   the command must reply to the query.

   Numeric Replies:

           ERR_NOSUCHSERVER              RPL_TIME
*/

bool	cmd_time(Server &server, Client &client, std::vector<std::string> &input)
{
	if (client.isRegistered() == false && client.isAuth() == false)
	{
		client.send_message(ERR_NOTREGISTERED(client.getNickname(), "TIME"));
		return false;
	}
	(void)server;
	if (input.size() > 1 && input[1] != SERVER_NAME)
	{
		client.send_message(ERR_NOSUCHSERVER(client.getNickname()));
		return false;
	}
	time_t	rawtime = time(NULL);
	std::string time = ctime(&rawtime);
	client.send_message(RPL_TIME(client.getNickname(), time));
	return true;
}
