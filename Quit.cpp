#include "User.hpp"

void User::quit(std::vector<std::string> cmd)
{
    this->usr_send("FUYEZ!!!");
	(void)cmd;
	close(this->userfd);
}
