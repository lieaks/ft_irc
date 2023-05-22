#pragma once

#include <vector>
#include <string>
#include "../includes/Server.hpp"

std::vector<std::string> split(std::string str, std::string delimiters);
std::string join(std::vector<std::string> vec, std::string delimiters, int pos);
void displayCommands();
std::string	ft_toupper(std::string str);