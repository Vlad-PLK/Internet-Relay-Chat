#include "SocketServer.hpp"

bool    Channel::userIsMember(const std::string name)
{
	for (std::vector<User>::iterator it = this->_channelUsers.begin(); it != this->_channelUsers.end(); ++it)
    {
        if (it->getNickname() == name)
            return (true);
    }
	return (false);
}

bool    Channel::userIsBanned(const std::string name)
{
    for (std::vector<User>::iterator it = this->_channelBanned.begin(); it != this->_channelBanned.end(); ++it)
    {
        if (it->getNickname() == name)
            return (true);
    }
	return (false);
}

bool    Channel::userIsInvited(const std::string name)
{
    for (std::vector<User>::iterator it = this->_channelInvited.begin(); it != this->_channelInvited.end(); ++it)
    {
        if (it->getNickname() == name)
            return (true);
    }
	return (false);
}

void    Channel::deleteUser(const std::string name)
{
    //need to know if the user has the rights to delete user

    for (std::vector<User>::iterator it = this->_channelUsers.begin(); it != this->_channelUsers.end(); ++it)
    {
        if (it->getNickname() == name)
        {
            it->deleteChannelRights(this->getTitle());
            this->_channelUsers.erase(it);
            break;
        }
    }

}