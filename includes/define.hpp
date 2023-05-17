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
#define RPL_WHOISSERVER(nickname, other_nickname) (":" + SERVER_NAME + "312 " + nickname + " " + other_nickname + SERVER_NAME + " :Password incorrect" + "\r\n")
#define RPL_ENDOFWHO(nickname, channel) (":" + SERVER_NAME + "315 " + nickname + " " + channel + " :End of /WHO list" + "\r\n")
#define RPL_WHOISIDLE(nickname, other_nickname, create_time) (":" + SERVER_NAME + "317 " + nickname + " " + other_nickname + " " + create_time + " :second idle, signon time" + "\r\n")
#define RPL_ENDOFWHOIS(nickname, other_nickname) (":" + SERVER_NAME + "318 " + nickname + " " + other_nickname + " :End of /WHOIS list" + "\r\n")
#define RPL_WHOREPLY(nickname, channel, username, concerned_client_nickname, status, mode) (":" + SERVER_NAME + "352 " + nickname + " " + channel + " ~" + username + " " + SERVER_NAME + " " + SERVER_NAME + " " + concerned_client_nickname + " " + status + mode + " :0" + username + "\r\n")
#define RPL_WHOREPLY_BIS(nickname, channel, username, concerned_client_nickname, status) (":" + SERVER_NAME + "352 " + nickname + " " + channel + " ~" + username + " " + SERVER_NAME + " " + SERVER_NAME + " " + concerned_client_nickname + " " + status + " :0" + username + "\r\n")
#define RPL_ENDOFWHOWAS(nickname, other_nickname) (":" + SERVER_NAME + "369 " + nickname + " " + other_nickname + " :End of /WHOWAS list" + "\r\n")

#define RPL_LISTSTART(nickname) (":" + SERVER_NAME + "321 " + nickname + " Channel :Users Name" + "\r\n")
#define RPL_LIST(nickname, channel, usercount) (":" + SERVER_NAME + "322 " + nickname + " " + channel + " " + usercount + " :" + "\r\n")
#define RPL_LISTEND(nickname) (":" + SERVER_NAME + "323 " + nickname + " :End of /LIST" + "\r\n")

#define ERR_NOSUCHNICK(nickname, other_nickname) (":" + SERVER_NAME + " 401 " + nickname + " " + other_nickname + ": No such nick/channel\r\n")
#define ERR_WASNOSUCHNICK(nickname, other_nickname) (":" + SERVER_NAME + " 406 " + nickname + " " + other_nickname + " :There was no such nickname\r\n")
#define ERR_NICKNAMEINUSE(nickname) (std::string(":") + SERVER_NAME + " 433 " + nickname + " :Nickname is already in use\r\n")

#define ERR_UNKNOWNCOMMAND(nickname, command) (std::string(":") + SERVER_NAME + " 421 " + nickname + " " + command + " :Unknown command")
#define ERR_NEEDMOREPARAMS(nickname, command) (std::string(":") + SERVER_NAME + " 461 " + nickname + " " + command + " :Not enough parameters\r\n")
#define ERR_ERRONEUSNICKNAME(nickname) (std::string(":") + SERVER_NAME + " 432 " + nickname + " :Erroneus nickname\r\n")

#define ERR_BADPING(nickname) (":" + SERVER_NAME + "513 " + nickname + " Badping" + "\r\n")
#define RPL_NAMREPLY(nickname, channel, list_client) (":" + SERVER_NAME + "353 " + nickname + " = " + channel + " :" + list_client  + "\r\n")
#define RPL_ENDOFNAMES(nickname, channel) (":" + SERVER_NAME + "366 " + nickname + " " + channel + " :End of /NAMES list" + "\r\n")
#define ERR_NOSUCHCHANNEL(nickname, channel) (":" + SERVER_NAME + "403 " + nickname + " " + channel + " :No such channel" + "\r\n")
#define ERR_CANNOTSENDTOCHAN(nickname, channel) (":" + SERVER_NAME + "404 " + nickname + " " + channel + " :Cannot send to channel" + "\r\n")
#define ERR_USERNOTINCHANNEL(nickname, channel, concerned_client_nickname) (":" + SERVER_NAME + "441 " + nickname + " " + concerned_client_nickname + " " + channel + " :They aren't on that channel" + "\r\n")
#define ERR_NOTONCHANNEL(nickname, channel) (":" + SERVER_NAME + "442 " + nickname + " " + channel + " :You're not on that chanel" + "\r\n")
#define ERR_INVITEONLYCHAN(nickname, channel) (":" + SERVER_NAME + "473 " + nickname + " " + channel + " :Cannot join channel (+i)" + "\r\n")
#define RPL_NOTOPIC(nickname, channel) (":" + SERVER_NAME + "331 " + nickname + " " + channel + " :No topic is set" + "\r\n")
#define RPL_TOPIC(nickname, channel, topic) (":" + SERVER_NAME + "332 " + nickname + " " + channel + "\r\n")
#define ROL_TOPICWHOTIME(nickname, channel, concerned_client_nickname, time) (":" + SERVER_NAME + "333 " + nickname + " " + channel + " " + concerned_client_nickname + " " + time + "\r\n")
