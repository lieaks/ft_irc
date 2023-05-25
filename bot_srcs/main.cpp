#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <cerrno>
#include <unistd.h>

#define LINK		"https://www.youtube.com/watch?v=dQw4w9WgXcQ"
#define BUFFER_SIZE 512

void sendData(int socket, const std::string& data) {
	std::string msg = data + "\r\n";
	if (send(socket, msg.c_str(), msg.length(), 0) == -1)
		throw std::runtime_error("Error sending data to server");
}

std::string receiveData(int socket) {
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	int bytesReceived = recv(socket, buffer, BUFFER_SIZE - 1, 0);
	if (bytesReceived == 0)
		throw std::runtime_error("Connection closed by server");
	if (bytesReceived < 0)
		throw std::runtime_error("Error receiving data from server");
	return std::string(buffer);
}

int main(int ac, char** av) {
	if (ac != 5) {
		std::cout << "Usage: " << av[0] << " <server> <port> <channel> <nickname>" << std::endl;
		return 1;
	}
	std::string server = "127.0.0.1";
	std::string password = av[2];
	std::string port = av[1];
	std::string channel = av[3];
	std::string nickname = av[4];
	if (channel[0] != '#')
		channel = "#" + channel;

	try {
		int socketDescriptor;
		struct addrinfo hints, *res;
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		if (getaddrinfo(server.c_str(), port.c_str(), &hints, &res))
			throw std::runtime_error("Failed to get address info");
		socketDescriptor = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (socketDescriptor == -1)
			throw std::runtime_error("Failed to create socket: ");
		if (connect(socketDescriptor, res->ai_addr, res->ai_addrlen) == -1)
			throw std::runtime_error("Failed to connect to server");
		freeaddrinfo(res);

		sendData(socketDescriptor, "PASS " + password);
		sendData(socketDescriptor, "NICK " + nickname);
		if (receiveData(socketDescriptor).find("NICK :" + nickname) == std::string::npos)
			throw std::runtime_error("Could not set nickname");
		sendData(socketDescriptor, "USER " + nickname + " 0 * :" + nickname);
		if (receiveData(socketDescriptor).find("001 " + nickname + " :") == std::string::npos)
			throw std::runtime_error("Could not set username");
		sendData(socketDescriptor, "JOIN " + channel);
		if (receiveData(socketDescriptor).find("JOIN :" + channel) == std::string::npos)
			throw std::runtime_error("Could not join channel");

		while (true) {
			std::string receivedData = receiveData(socketDescriptor);
			std::cout << receivedData;

			if (receivedData.find("PRIVMSG " + channel) != std::string::npos) {
				std::string messageSender = receivedData.substr(1, receivedData.find('!') - 1);
				std::string messageContent = receivedData.substr(receivedData.find(" :") + 2);
				if (messageContent.find("hello") != std::string::npos) {
					std::string response = "PRIVMSG " + channel + " :Hello, " + messageSender + "! ";
					sendData(socketDescriptor, response);
				}
				if (messageContent.find("link") != std::string::npos) {
					std::string response = "PRIVMSG " + channel + " :" + LINK;
					sendData(socketDescriptor, response);
				}
			}
		}
		close(socketDescriptor);
	} catch (std::exception &e) {
		std::cerr << e.what();
		if (errno != 0)
			std::cerr << ": " << strerror(errno);
		std::cerr << std::endl;
		return 1;
	}
	return 0;
}
