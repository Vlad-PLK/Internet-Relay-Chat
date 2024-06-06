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
    {
        if (this->userIsMember(user.getNickname()) == false)
            this->_channelUsers.push_back(&user);
        this->_channelOperators.push_back(&user);
        this->channelWelcome(user);
    }
}

bool    Channel::setOperators(User &user, bool flag) //flag 0 means delete from channelOperators and adds it to channelUsers, 1 means to add the user as an operator
{
    //need to know if the user has the rights to add or delete operator
    if (!flag && this->userIsOperator(user.getNickname()))
    {
        user.setNickname(user.getNickname().substr(1));
        this->addUser(user);
        this->deleteOperator(user.getNickname());
        return true;
    }
    else
    {
        if (userIsMember(user.getNickname()))
        {
            this->addOperator(user);
            this->deleteUser(user.getNickname());
            return true;
        }
    }
    return false;
}

void    Channel::deleteOperator(std::string name)
{
    if (name[0] != '@')
        name.insert(0, 1, '@');
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
