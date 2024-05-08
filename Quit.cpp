#include "User.hpp"

void User::quit(std::vector<std::string> cmd)
{
    this->sendAndPrint("FUYEZ!!!", 13, 0);
	(void)cmd;
	close(this->userfd);
}

void User::hello(std::vector<std::string> cmd)
{
    this->sendAndPrint("ICI C'EST IRC", 13, 0);
	(void)cmd;
}
