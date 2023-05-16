#pragma once

#include "Client.hpp"

bool	cmd_nick(Client &client, std::vector<std::string> &input);
bool	cmd_user(Client &client, std::vector<std::string> &input);
bool	cmd_pass(Client &client, std::vector<std::string> &input);
