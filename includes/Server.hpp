#include <string>
#include <map>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "Client.hpp"

class Server
{
private:
	Server(){};
	
	// member attributes
	int 							_port;
	std::string						_password;
	int								_socket_fd;
	struct sockaddr_in				_socket_addr;
	std::map<std::string, Client*>	_server;

public:
	Server(int port, std::string password);
	~Server();
};

class CustomException : public std::exception {
	private:
		const char* m_message;
	public:
		CustomException(const char * message) : m_message(message) {};
		virtual const char* what() const throw() {return m_message;};
};
