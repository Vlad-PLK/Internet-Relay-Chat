#include "User.hpp"

void User::quit(std::vector<std::string> cmd)
{
    this->my_send("FUYEZ!!!", 8, 0);
	(void)cmd;
	close(this->userfd);
}
