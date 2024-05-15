#include "Channel.hpp"

Channel::Channel()
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

std::string Channel::getModes() const
{
    return (this->_modes);
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

std::vector<User> &Channel::getChannelBanned()
{
    return (this->_channelBanned);
}

void Channel::setTitle(std::string title)
{
    // if (this->userIsOperator(user.getNickname()))
        this->_title = title;
    //ERROR MSG (user does not have the rights)
}

void Channel::setPassword(std::string pass)
{
    // if (this->userIsOperator(user.getNickname()))
        this->_password = pass;
    //ERROR MSG (user does not have the rights)
}

void Channel::setTopic(std::string topic)
{
    // if (this->userIsOperator(user.getNickname()) || user.checkRights(this->_title, "t"))
        this->_topic = topic;
}

void Channel::setMode(std::string modes)
{
    this->_modes = modes;
}

std::string Channel::removeMode(std::string &str, char mode)
{
    std::string result;
    for (std::string::size_type i = 0; i < str.size(); ++i)
    {
        if (str[i] != mode)
            result += str[i];
    }
    return (result);
}


// Need to check if user is an operator !!
void Channel::setMode(std::string new_modes, int flag) // flag == 0 means remove and flag == 1 means add
{

    int i = 0;
    while (new_modes[++i])
    {
        if (!flag)
        {
            if (this->_modes.find(new_modes[i]))
                this->setMode(removeMode(this->_modes, new_modes[i]));
            // else
                // ERROR MESSAGE (?) the mode to delete is not preset
        }
        else
        {
            if (!this->_modes.find(new_modes[i]))
                this->setMode(this->_modes + new_modes[i]);
            // else
                // ERROR MESSAGE (?) the mode to add exists already
        }
    }
}

void Channel::setLimit(int limit)
{
    // if (this->userIsOperator(user.getNickname()))
    this->_limit = limit;
}

void    Channel::addUser(User &user)
{
    if ((int)(this->_channelUsers.size() + this->_channelOperators.size()) < this->_limit)
    {
        if ((int)(this->_channelUsers.size() + this->_channelOperators.size()) == 0)
            this->addOperator(user);
        else
        {
            // need a checker for banned user
            this->_channelUsers.push_back(user);
            user.getChannelRights().insert(std::make_pair(this->_title, this->getModes())); // (?) what are the basic rights for a normal user
        }
    }
    // else
        // ERROR MSG (channel is full)
}

bool    Channel::userIsMember(std::string name)
{
	for (std::vector<User>::iterator it = this->_channelUsers.begin(); it != this->_channelUsers.end(); ++it)
    {
        if (it->getNickname() == name)
            return (true);
    }
	return (false);
}

bool    Channel::userIsOperator(std::string name)
{
	for (std::vector<User>::iterator it = this->_channelOperators.begin(); it != this->_channelOperators.end(); ++it)
    {
        if (it->getNickname() == name)
            return (true);
    }
	return (false);
}

void    Channel::addOperator(User &user)
{
    User userCopy = user;
    userCopy.setNickname('@' + userCopy.getNickname());
    if (!this->userIsOperator(userCopy.getNickname()))
    {
        this->_channelOperators.push_back(userCopy);
        this->deleteUser(user.getNickname());
    }
}

bool    Channel::userIsBanned(std::string name)
{
    for (std::vector<User>::iterator it = this->_channelBanned.begin(); it != this->_channelBanned.end(); ++it)
    {
        if (it->getNickname() == name)
            return (true);
    }
	return (false);
}

void    Channel::setOperators(User &user, int flag) //flag 0 means delete from channelOperators and adds it to channelUsers, 1 means to add the user as an operator
{
    //need to know if the user has the rights to add or delete operator

    if (!flag && this->userIsOperator(user.getNickname()))
    {
        user.setNickname(user.getNickname().substr(1));
        this->addUser(user);
        this->deleteOperator(user.getNickname());
    }
    else
    {
        if (userIsMember(user.getNickname()))
            this->addOperator(user);
        // else
            // user is not in the channel or already Op
    }
}

void    Channel::deleteUser(std::string name)
{
    //need to know if the user has the rights to delete user

    for (std::vector<User>::iterator it = this->_channelUsers.begin(); it != this->_channelUsers.end(); ++it)
    {
        if (it->getNickname() == name)
        {
            this->_channelUsers.erase(it);
            break;
        }
    }
}

void    Channel::deleteOperator(std::string name)
{
    //need to know if the user has the rights to delete user

    for (std::vector<User>::iterator it = this->_channelOperators.begin(); it != this->_channelOperators.end(); ++it)
    {
        if (it->getNickname() == name)
        {
            this->_channelOperators.erase(it);
            break;
        }
    }
}