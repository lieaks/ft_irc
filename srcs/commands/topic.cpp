#include "../../includes/commands.hpp"

bool	cmd_topic(Server &server, Client &client, std::vector<std::string> &input) {
	(void)server;
	if (input.size() < 2) {
		client.send_message(ERR_NEEDMOREPARAMS(client.getNickname(), "TOPIC"));
		return false;
	}
	Channel *channel = client.getChannel(input[1].substr(1));
	if (!channel) {
		client.send_message(ERR_NOTONCHANNEL(client.getNickname(), input[1]));
		return false;
	}
	if (input.size() == 2) {
		if (channel->getTopic().empty())
			client.send_message(RPL_NOTOPIC(client.getNickname(), channel->getName()));
		else
			client.send_message(RPL_TOPIC(client.getNickname(), channel->getName(), channel->getTopic()));
		return true;
	}
	std::string topic = join(input, " ", 2);
	if (channel->isModeSet(TOPIC_PROTECTED) && !(channel->isOperator(&client) || channel->isCreator(&client) || client.isModeSet(OPERATOR))) {
		client.send_message(ERR_CHANOPRIVSNEEDED(client.getNickname(), channel->getName()));
		return false;
	}
	if (topic[0] == ':')
		topic = topic.substr(1);
	channel->setTopic(topic);
	channel->send_message(TOPIC(client.getNickname(), client.getUsername(), channel->getName(), channel->getTopic()));
	return true;
}
