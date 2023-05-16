#pragma once

#include "Client.hpp"

class Server;

#define NICK_VALID_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_[]{}'|"

bool	cmd_nick(Server &server, Client &client, std::vector<std::string> &input);
bool	cmd_user(Server &server, Client &client, std::vector<std::string> &input);
bool	cmd_pass(Server &server, Client &client, std::vector<std::string> &input);

#include "Server.hpp"
