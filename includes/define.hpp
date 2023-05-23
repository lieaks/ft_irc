#pragma once

#define	SERVER_NAME "chat-astrophe"
#define BACKLOG 10 //max length of the queue
#define max_clients 10
#define MAX_EVENTS 10
#define BUFFER_SIZE 1024
#define VERSION "1"
#define DEFAULT_OPER_PASS "password"

#define FORMAT_REPLY(num_rply_numb, nickname) (std::string(":") + SERVER_NAME + " " + num_rply_numb + " " + nickname + " ")
#define CLIENT_ID(nickname, username, command) (":" + nickname + "!~" + username + "@" + SERVER_NAME + " " + command + " ")

// Reponses numeriques
#define RPL_WELCOME(nickname) (std::string(":") + SERVER_NAME + " 001 " + nickname + " :Welcome to the Internet Relay Network " + nickname + "\r\n")
#define RPL_YOURHOST(nickname) (std::string(":") + SERVER_NAME + " 002 " + nickname + " Your host is " + SERVER_NAME + ", running version " + VERSION + "\r\n")
#define RPL_CREATED(nickname, date) (std::string(":") + SERVER_NAME + " 003 " + nickname + " :This server was created " + date + "\r\n")
#define RPL_MYINFO(nickname) (std::string(":") + SERVER_NAME + " 004 " + nickname + " " + SERVER_NAME + " " + VERSION + "\r\n")
#define RPL_INFO(nickname) (std::string(":") + SERVER_NAME + " 371 " + nickname + " :" + SERVER_NAME + "\r\n" + \
							":" + SERVER_NAME + " 371 " + nickname + " :" + "written by dly, lgillard, axlamber" + "\r\n" + \
							":" + SERVER_NAME + " 371 " + nickname + " :" + "version 1.0" + "\r\n")


#define RPL_VERSION(nickname) (FORMAT_REPLY(" 351", nickname) + "version " + VERSION + " " + SERVER_NAME + " :Version of ircserv " + "\r\n")
#define RPL_TIME(nickname, time) (FORMAT_REPLY(" 391", nickname) + SERVER_NAME + " :" + time + "\r\n")
#define ERR_NOSUCHSERVER(nickname) (FORMAT_REPLY(" 402", nickname) + SERVER_NAME + " :" + "\r\n")
#define RPL_ENDOFINFO(nickname) (std::string(":") + SERVER_NAME + " 374 " + nickname + " " + ":End of /INFO list. " + "\r\n")
#define RPL_CHANNELMODEIS(nickname, channel, channel_mode) (std::string(":") + SERVER_NAME + " 324 " + nickname + " " + channel + " " + channel_mode + "\r\n")
#define RPL_CREATIONTIME(nickname, channel, date) (std::string(":") + SERVER_NAME + " 329 " + nickname + " " + channel + " " + date + "\r\n")
#define RPL_ENDOFBANLIST(nickname, channel) (std::string(":") + SERVER_NAME + " 368 " + nickname + " " + channel + " :End of channel ban list" + "\r\n")
#define ERR_UNKNOWNMODE(nickname, mode) (std::string(":") + SERVER_NAME + " 472 " + nickname + " " + mode + " :is unknown mode char to me" + "\r\n")
#define ERR_BANNEDFROMCHAN(nickname, channel) (std::string(":") + SERVER_NAME + " 474 " + nickname + " " + channel + " :Cannot join channel (+b)" + "\r\n")
#define ERR_NOPRIVILEGES(nickname) (std::string(":") + SERVER_NAME + " 481 " + nickname + " :Permission Denied- You're not an IRC operator" + "\r\n")
#define ERR_CHANPRIVSNEED(nickname, channel) (std::string(":") + SERVER_NAME + " 482 " + nickname + " " + channel + " :You're not channel operator" + "\r\n")
#define ERR_UMODEUNKNOWNFLAG(nickname) (std::string(":") + SERVER_NAME + " 501 " + nickname + " :Unknown MODE flag" + "\r\n")
#define ERR_PASSWDMISMATCH(nickname) (std::string(":") + SERVER_NAME + " 464 " + nickname + " :Password incorrect" + "\r\n")

#define RPL_WHOISUSER(nickname, other_nickname, username) (std::string(":") + SERVER_NAME + " 311 " + nickname + " " + other_nickname + " ~" + username + " " + SERVER_NAME + " * ;" + username + "\r\n")
#define RPL_WHOISSERVER(nickname, other_nickname) (std::string(":") + SERVER_NAME + " 312 " + nickname + " " + other_nickname + SERVER_NAME + " :Password incorrect" + "\r\n")
#define RPL_ENDOFWHO(nickname, channel) (std::string(":") + SERVER_NAME + " 315 " + nickname + " " + channel + " :End of /WHO list" + "\r\n")
#define RPL_WHOISIDLE(nickname, other_nickname, create_time) (std::string(":") + SERVER_NAME + " 317 " + nickname + " " + other_nickname + " " + create_time + " :second idle, signon time" + "\r\n")
#define RPL_ENDOFWHOIS(nickname, other_nickname) (std::string(":") + SERVER_NAME + " 318 " + nickname + " " + other_nickname + " :End of /WHOIS list" + "\r\n")
#define RPL_WHOREPLY(nickname, channel, username, concerned_client_nickname, status, mode) (std::string(":") + SERVER_NAME + " 352 " + nickname + " " + channel + " ~" + username + " " + SERVER_NAME + " " + SERVER_NAME + " " + concerned_client_nickname + " " + status + mode + " :0" + username + "\r\n")
#define RPL_WHOREPLY_BIS(nickname, channel, username, concerned_client_nickname, status) (std::string(":") + SERVER_NAME + " 352 " + nickname + " " + channel + " ~" + username + " " + SERVER_NAME + " " + SERVER_NAME + " " + concerned_client_nickname + " " + status + " :0" + username + "\r\n")
#define RPL_ENDOFWHOWAS(nickname, other_nickname) (std::string(":") + SERVER_NAME + " 369 " + nickname + " " + other_nickname + " :End of /WHOWAS list" + "\r\n")

#define RPL_LISTSTART(nickname) (std::string(":") + SERVER_NAME + " 321 " + nickname + " Channel :Users Name" + "\r\n")
#define RPL_LIST(nickname, channel, usercount) (std::string(":") + SERVER_NAME + " 322 " + nickname + " " + channel + " " + usercount + " :" + "\r\n")
#define RPL_LISTEND(nickname) (std::string(":") + SERVER_NAME + " 323 " + nickname + " :End of /LIST" + "\r\n")

#define ERR_NOSUCHNICK(nickname, other_nickname) (std::string(":") + SERVER_NAME + " 401 " + nickname + " " + other_nickname + " :No such nick\r\n")
#define ERR_WASNOSUCHNICK(nickname, other_nickname) (std::string(":") + SERVER_NAME + " 406 " + nickname + " " + other_nickname + " :There was no such nickname\r\n")
#define ERR_NICKNAMEINUSE(nickname) (std::string(":") + SERVER_NAME + " 433 " + nickname + " :Nickname is already in use\r\n")


#define ERR_NORECIPIENT(nickname, command) (std::string(":") + SERVER_NAME + " 411 " + nickname + " :No recipient given " + command + "\r\n")
#define ERR_NOTEXTTOSEND(nickname) (std::string(":") + SERVER_NAME + " 412 " + nickname + " :No text to send " + "\r\n")
#define ERR_UNKNOWNCOMMAND(nickname, command) (std::string(":") + SERVER_NAME + " 421 " + nickname + " " + command + " :Unknown command")
#define ERR_NEEDMOREPARAMS(nickname, command) (std::string(":") + SERVER_NAME + " 461 " + nickname + " " + command + " :Not enough parameters\r\n")
#define ERR_ALREADYREGISTRED(nickname) (std::string(":") + SERVER_NAME + " 462 " + nickname + " :Already registred\r\n")
#define ERR_ERRONEUSNICKNAME(nickname) (std::string(":") + SERVER_NAME + " 432 " + nickname + " :Erroneus nickname\r\n")
#define ERR_NOORIGIN(nickname) (std::string(":") + SERVER_NAME + " 409 " + nickname + " :No origin\r\n")

#define ERR_BADPING(nickname) (std::string(":") + SERVER_NAME + " 513 " + nickname + " Badping" + "\r\n")
#define RPL_NAMREPLY(nickname, channel, list_client) (std::string(":") + SERVER_NAME + " 353 " + nickname + " = " + channel + " :" + list_client  + "\r\n")
#define RPL_ENDOFNAMES(nickname, channel) (std::string(":") + SERVER_NAME + " 366 " + nickname + " " + channel + " :End of /NAMES list" + "\r\n")
#define ERR_NOSUCHCHANNEL(nickname, channel) (std::string(":") + SERVER_NAME + " 403 " + nickname + " " + channel + " :No such channel" + "\r\n")
#define ERR_CANNOTSENDTOCHAN(nickname, channel) (std::string(":") + SERVER_NAME + " 404 " + nickname + " " + channel + " :Cannot send to channel" + "\r\n")
#define ERR_USERNOTINCHANNEL(nickname, channel, concerned_client_nickname) (std::string(":") + SERVER_NAME + " 441 " + nickname + " " + concerned_client_nickname + " " + channel + " :They aren't on that channel" + "\r\n")
#define ERR_NOTONCHANNEL(nickname, channel) (std::string(":") + SERVER_NAME + " 442 " + nickname + " " + channel + " :You're not on that chanel" + "\r\n")
#define ERR_INVITEONLYCHAN(nickname, channel) (std::string(":") + SERVER_NAME + " 473 " + nickname + " " + channel + " :Cannot join channel (+i)" + "\r\n")
#define RPL_NOTOPIC(nickname, channel) (std::string(":") + SERVER_NAME + " 331 " + nickname + " " + channel + " :No topic is set" + "\r\n")
#define RPL_TOPIC(nickname, channel, topic) (std::string(":") + SERVER_NAME + " 332 " + nickname + " " + channel + "\r\n")
#define ROL_TOPICWHOTIME(nickname, channel, concerned_client_nickname, time) (std::string(":") + SERVER_NAME + " 333 " + nickname + " " + channel + " " + concerned_client_nickname + " " + time + "\r\n")
#define RPL_INVITING(nickname, target, channel) (std::string(":") + SERVER_NAME + " 341 " + nickname + " " + target + " " + channel + "\r\n")
#define RPL_YOUROPER(nickname) (std::string(":") + SERVER_NAME + " 381 " + nickname + " :You are now an IRC operator" + "\r\n")
#define ERR_NOTREGISTERED(nickname) (std::string(":") + SERVER_NAME + " 451 " + nickname + " :You have not registered" + "\r\n")

// macro command format
#define PONG(nickname) (std::string(":") + SERVER_NAME + " PONG " + SERVER_NAME + " :" + SERVER_NAME + "\r\n")
#define NICK(nickname, username, new_nickname) (CLIENT_ID(nickname, username, "NICK") + ":" + new_nickname + "\r\n")
#define NOTICE(nickname, username, cmd, message) (CLIENT_ID(nickname, username, cmd) + ":" + message + "\r\n")
#define PRIVMSG(nickname, username, dest_nickname, msg) (CLIENT_ID(nickname, username, "PRIVMSG") + dest_nickname + " :" + msg + "\r\n")
