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

std::vector<User> &Channel::getChannelUsers()
{
    return (this->_channelUsers);
}

std::vector<User> &Channel::getChannelOperators()
{
    return (this->_channelOperators);
}

void Channel::setTitle(std::string title)
{
    this->_title = title;
}

void Channel::setPassword(std::string pass)
{
    this->_password = pass;
}

void Channel::setTopic(std::string topic)
{
    this->_topic = topic;
}

// void Channel::setMode(char new_mode)
// {
//     this->_mode = new_mode;
// }


void Channel::addUser(User *user)
{
    if (this->_channelUsers.size() < this->_limit)
    {
        if (this->_channelUsers.size() == 0)

    }

}
