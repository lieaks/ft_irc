#include "../includes/Client.hpp"

Client::Client(int client_fd, std::string hostname) :
	_client_fd(client_fd), _hostname(hostname) {
		std::cout << "new client with fd: " << _client_fd << std::endl;
	};

const std::string Client::getInput() const {
	return _input;
};

void Client::setInput(std::string input) {
	_input = input;
};

void Client::clearInput() {
	_input.clear();
}
