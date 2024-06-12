#include "SocketServer.hpp"

bool    Channel::userIsOperator(const std::string name)
{
	for (std::vector<User *>::iterator it = this->_channelOperators.begin(); it != this->_channelOperators.end(); it++)
    {
        if ((*it)->getNickname() == name)
            return (true);
    }
	return (false);
}

void    Channel::addOperator(User &user)
{
    if (!this->userIsOperator(user.getNickname()))
        this->_channelOperators.push_back(&user);
}

bool    Channel::setOperators(User &user, bool flag) //flag 0 means delete from channelOperators and adds it to channelUsers, 1 means to add the user as an operator
{
    if (!flag)
    {
        if (this->userIsOperator(user.getNickname()))
        {
            this->deleteOperator(user.getNickname());
            return true;
        }
    }
    else
    {
        if (userIsMember(user.getNickname()))
        {
            this->addOperator(user);
            return true;
        }
    }
    return false;
}

void    Channel::deleteOperator(std::string name)
{
    for (std::vector<User *>::iterator it = this->_channelOperators.begin(); it != this->_channelOperators.end(); ++it)
    {
        if ((*it)->getNickname() == name)
        {
            (*it)->deleteChannelRights(this->getTitle());
            this->_channelOperators.erase(it);
            break;
        }
    }
}
