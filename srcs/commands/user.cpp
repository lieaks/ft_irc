#include "../../includes/commands.hpp"

/*
   Command: USER
   Parameters: <username> <hostname> <servername> <realname>

   The USER command is used to register a new user with the server. The
   <username> parameter is the username of the new user, the <hostname>
   parameter is the hostname of the computer the user is connecting from,
   the <servername> parameter is the name of the server the user is
   connecting to, and the <realname> parameter is the real name of the user.

   Numeric Replies:

           ERR_NEEDMOREPARAMS
           ERR_ALREADYREGISTRED
           RPL_WELCOME
*/

bool	cmd_user(Server &server, Client &client, std::vector<std::string> &input) {
	std::string	realname;

	(void)server;
	if (input.size() < 5) {
		client.send_message(ERR_NEEDMOREPARAMS(client.getNickname(), input[0]));
		return false;
	}
	if (client.isRegistered()) {
		client.send_message(ERR_ALREADYREGISTRED(client.getNickname()));
		return false;
	}
	client.setUsername(input[1]);

	realname = input[4];
	for (size_t i = 5; i < input.size(); i++)
		realname += " " + input[i];
	if (realname[0] == ':')
		realname = realname.substr(1);
	client.setRealname(realname);
	client.addMode(WALLOPS);
	if (!client.getNickname().empty() && !client.getUsername().empty() && !client.getRealname().empty())
		client.setRegistered(true);
	if (client.isRegistered() && client.isAuth())
		client.send_message(RPL_WELCOME(client.getNickname()));
	return true;
}
