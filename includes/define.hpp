#pragma once

#define	SERVER_NAME "chattastrophe"
#define BACKLOG 10 //max length of the queue
#define max_clients 10
#define MAX_EVENTS 10
#define BUFFER_SIZE 1024
#define VERSION 1

// Reponses numeriques
#define RPL_WELCOME(nickname) (":" + SERVER_NAME + " 001 " + nickname + " :Welcome to the Internet Relay Network " + nickname + "\r\n")
#define RPL_YOURHOST(nickname) (":" + SERVER_NAME + " 002 " + nickname + " Your host is " + SERVER_NAME + ", running version " + VERSION + "\r\n")
#define RPL_CREATED(nickname, date) (":" + SERVER_NAME + " 003 " + nickname + " :This server was created " + date + "\r\n")
#define RPL_MYINFO(nickname) (":" + SERVER_NAME + " 004 " + nickname + " " + SERVER_NAME + " " + VERSION + "\r\n")

#define RPL_CHANNELMODEIS(nickname, channel, channel_mode) (":" + SERVER_NAME + " 324 " + nickname + " " + channel + " " + channel_mode + "\r\n")
#define RPL_CREATIONTIME(nickname, channel, date) (":" + SERVER_NAME + " 329 " + nickname + " " + channel + " " + date + "\r\n")
#define RPL_ENDOFBANLIST(nickname, channel) (":" + SERVER_NAME + " 368 " + nickname + " " + channel + " :End of channel ban list" + "\r\n")
#define ERR_UNKNOWNMODE(nickname, mode) (":" + SERVER_NAME + " 472 " + nickname + " " + mode + " :is unknown mode char to me" + "\r\n")
#define ERR_BANNEDFROMCHAN(nickname, channel) (":" + SERVER_NAME + " 474 " + nickname + " " + channel + " :Cannot join channel (+b)" + "\r\n")
#define ERR_NOPRIVILEGES(nickname) (":" + SERVER_NAME + " 481 " + nickname + " :Permission Denied- You're not an IRC operator" + "\r\n")
#define ERR_CHANPRIVSNEED(nickname, channel) (":" + SERVER_NAME + " 482 " + nickname + " " + channel + " :You're not channel operator" + "\r\n")
#define ERR_UMODEUNKNOWNFLAG(nickname) (":" + SERVER_NAME + "501 " + nickname + " :Unknown MODE flag" + "\r\n")
#define ERR_PASSWDMISMATCH(nickname) (":" + SERVER_NAME + "464 " + nickname + " :Password incorrect" + "\r\n")

#define RPL_WHOISUSER(nickname, other_nickname, username) (":" + SERVER_NAME + "311 " + nickname + " " + other_nickname + " ~" + username + " " + SERVER_NAME + " * ;" + username + "\r\n")
#define RPL_WHOISSERVER(nickname, other_nickname) (":" + SERVER_NAME + "312 " + nickname + " " + other_nickname + " :Password incorrect" + "\r\n")

#define ERR_NOSUCHNICK(nickname, other_nickname) (":" + SERVER_NAME + " 401 " + nickname + " " + other_nickname + ": No such nick/channel\r\n")
#define ERR_WASNOSUCHNICK(nickname, other_nickname) (":" + SERVER_NAME + " 406 " + nickname + " " + other_nickname + " :There was no such nickname\r\n")

#define ERR_NEEDMOREPARAMS(command) (std::string(":") + SERVER_NAME + " 461 " + command + " :Not enough parameters\r\n")

#define ERR_ERRONEUSNICKNAME(nickname) (std::string(":") + SERVER_NAME + " 432 " + nickname + " :Erroneus nickname\r\n")
#define ERR_NICKNAMEINUSE(nickname) (std::string(":") + SERVER_NAME + " 433 " + nickname + " :Nickname is already in use\r\n")
