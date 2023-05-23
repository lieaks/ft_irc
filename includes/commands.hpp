#pragma once

#include "Client.hpp"
#include "define.hpp"
#include "Server.hpp"

class Server;

#define NICK_VALID_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_[]{}'|"

bool	cmd_nick(Server &server, Client &client, std::vector<std::string> &input);
bool	cmd_user(Server &server, Client &client, std::vector<std::string> &input);
bool	cmd_pass(Server &server, Client &client, std::vector<std::string> &input);
bool	cmd_ping(Server &server, Client &client, std::vector<std::string> &input);
bool	cmd_info(Server &server, Client &client, std::vector<std::string> &input);
bool	cmd_version(Server &server, Client &client, std::vector<std::string> &input);
bool	cmd_time(Server &server, Client &client, std::vector<std::string> &input);
bool	cmd_invite(Server &server, Client &client, std::vector<std::string> &input);
bool	cmd_oper(Server &server, Client &client, std::vector<std::string> &input);
bool	cmd_notice(Server &server, Client &client, std::vector<std::string> &input);
bool	cmd_privmsg(Server &server, Client &client, std::vector<std::string> &input);
bool	cmd_wallops(Server &server, Client &client, std::vector<std::string> &input);
bool	cmd_quit(Server &server, Client &client, std::vector<std::string> &input);
bool	cmd_cap(Server &server, Client &client, std::vector<std::string> &input);
bool	cmd_join(Server &server, Client &client, std::vector<std::string> &input);
bool	cmd_squit(Server &server, Client &client, std::vector<std::string> &input);
