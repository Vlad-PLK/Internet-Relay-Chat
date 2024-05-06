#include "User.hpp"

void User::quit(std::vector<std::string> cmd)
{
    std::cout << "HERE quit" << std::endl;
	(void)cmd;
	close(this->userfd);
}

void User::hello(std::vector<std::string> cmd)
{
    std::cout << "HERE hello" << std::endl;
	(void)cmd;
}
