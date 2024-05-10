#include "Channel.hpp"

Channel::Channel(void)
{

}

Channel::~Channel(void)
{

}

std::string Channel::getTitle() const
{
    return (this->_title);
}
 
std::string &Channel::getPassword()
{
    return (this->_password);
}

std::string Channel::getTopic() const
{
    return (this->_topic);
}

std::string Channel::getMode() const
{
    return (this->_mode);
}

int Channel::getLimit() const
{
    return (this->_limit);
}

std::vector<User> &Channel::getChannelUsers()
{
    return (this->_channelUsers);
}

std::vector<User> &Channel::getChannelOperators()
{
    return (this->_channelOperators);
}

void Channel::setTitle(User &user, std::string title)
{
    if (user.isChannelOper(getChannelOperators()))
        this->_title = title;
    //ERROR MSG (user does not have the rights)
}

void Channel::setPassword(User &user, std::string pass)
{
    if (user.isChannelOper(getChannelOperators()))
        this->_password = pass;
    //ERROR MSG (user does not have the rights)
}

void Channel::setTopic(User &user, std::string topic)
{
    if (user.isChannelOper(getChannelOperators()) || user.checkRights(this->_title, "t"))
        this->_topic = topic;
    //ERROR MSG (user does not have the rights)
}

// void Channel::setMode(User &user, char new_mode)
// {
//     this->_mode = new_mode;
// }

void Channel::setLimit(User &user, int limit)
{
    if (user.isChannelOper(getChannelOperators()))
        this->_limit = limit;
}

void    Channel::addUser(const User &user)
{
    if ((int)this->_channelUsers.size() < this->_limit)
    {
        if ((int)this->_channelUsers.size() == 0)
        {
            User userCopy = user;
            userCopy.setNickname('@' + userCopy.getNickname());
            this->_channelOperators.push_back(userCopy);
        }
        else
        {
            this->_channelUsers.push_back(user);
            user.getChannelRights().insert(std::make_pair(this->_title, "blabla")); // (?) what are the basic rights for a normal user
        }
    }
    // else
        // ERROR MSG (channel is full)
}
