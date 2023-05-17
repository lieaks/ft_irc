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
#define RPL_MYINFO(nickname) (":" + SERVER_NAME + " 004 " + nickname + SERVER_NAME + VERSION + "\r\n")

#define ERR_NOSUCHNICK(nickname, other_nickname) (":" + SERVER_NAME + " 401 " + nickname + " " + other_nickname + ": No such nick/channel\r\n")
#define ERR_WASNOSUCHNICK(nickname, other_nickname) (":" + SERVER_NAME + " 406 " + nickname + " " + other_nickname + " :There was no such nickname\r\n")
#define ERR_NICKNAMEINUSE(nickname) (":" + SERVER_NAME + " 433 " + " :Nickname is already in use\r\n")
#define ERR_NEEDMOREPARAMS(command) (std::string(":") + SERVER_NAME + " 461 " + command + " :Not enough parameters\r\n")

