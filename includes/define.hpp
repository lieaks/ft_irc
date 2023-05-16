#pragma once

#define	SERVER_NAME chatastrophe
#define BACKLOG 10 //max length of the queue
#define max_clients 10
#define MAX_EVENTS 10
#define BUFFER_SIZE 1024

// Reponses numeriques
// 401
#define ERR_NOSUCHNICK(nickname, other_nickname) (":" + SERVER_NAME + " 401 " + nickname + " " + other_nickname + ": No such nick/channel")
