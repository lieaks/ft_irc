#include "../includes/utils.hpp" 

std::vector<std::string> split(std::string str, std::string delimiters){
	std::vector<std::string>	tokens;
	std::string					ret;
	size_t						pos = 0;

	while ((pos = str.find(delimiters)) != std::string::npos){
		ret = str.substr(0, pos);
		str = str.substr(pos + 1);
		if (!ret.empty())
			tokens.push_back(ret);
	}
	if (!str.empty())
		tokens.push_back(str);
	return tokens;
};

std::string join(std::vector<std::string> vec, std::string delimiters, int pos)
{
	std::string res;
	for (std::vector<std::string>::iterator it = vec.begin() + pos; it != vec.end(); it++)
	{
		res.append(*it);
		if (it != vec.end() - 1)
			res.append(delimiters);
	}
	return res;
}

void displayCommands(Client *client, std::string arg) {
	std::cout << "from [" << client->getInput() << " ] ";
	std::cout << arg << std::endl;
}
