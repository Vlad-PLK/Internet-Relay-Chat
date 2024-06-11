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

std::vector<User*> &Channel::getChannelUsers()
{
    return (this->_channelUsers);
}

std::vector<User*> &Channel::getChannelOperators()
{
    return (this->_channelOperators);
}

std::vector<User*> &Channel::getChannelBanned()
{
    return (this->_channelBanned);
}

std::vector<User*> &Channel::getChannelInvited()
{
    return (this->_channelInvited);
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

void    Channel::setLimit(int limit)
{
    this->_limit = limit;
}

void    Channel::channelWelcome(User &user)
{
    std::string users;
    for (size_t i = 0; i != this->_channelUsers.size(); i++)
    {
        if (this->userIsOperator(this->_channelUsers[i]->getNickname()) == true)
            users.append("@");
        users.append(this->_channelUsers[i]->getNickname());
        users.append(" ");
    }

    std::vector<User *>::iterator it;
    for (it = this->_channelUsers.begin(); it != this->_channelUsers.end(); it++)
    {
        (*it)->usr_send(RPL_JOIN(user.getNickname() + "!~" + user.getUsername() + "@" + user.getIp(), this->_title));
        if (this->_topic != "")
            (*it)->usr_send(RPL_TOPIC((user.getNickname() + "!" + user.getUsername() + "@" + user.getIp()), this->_title, this->_topic));
        if ((*it)->getNickname() == user.getNickname())
        {
            (*it)->usr_send(RPL_NAMREPLY(user.getNickname(), "=", this->_title, users));
            (*it)->usr_send(RPL_ENDOFNAMES(user.getNickname(), this->_title));
        }
    }
}

void    Channel::addInvited(User &user)
{
    if (!this->userIsInvited(user.getNickname()))
        this->_channelInvited.push_back(&user);
    std::cout << "INVITED :" << std::endl;
    for (std::vector<User *>::iterator it = this->_channelInvited.begin(); it != this->_channelInvited.end(); ++it)
        std::cout << (*it)->getNickname() << std::endl;
}

void    Channel::addUser(User &user)
{
    if ((int)((this->_channelUsers.size() + this->_channelOperators.size())) < this->getLimit() || this->getLimit() == -1)
    {
        // if there's no users yet
        if ((int)(this->_channelUsers.size() + this->_channelOperators.size()) == 0)
        {
        // first user becomes operator //
            this->_channelUsers.push_back(&user);
            this->addOperator(user);
            this->channelWelcome(user);
        }
        else
        {
            if (!userIsMember(user.getNickname()) && !userIsOperator(user.getNickname()) && !userIsBanned(user.getNickname()))
            {
                if (this->getModes().find('i') == std::string::npos) // Not invite-only
                {
                    this->_channelUsers.push_back(&user);
                    this->channelWelcome(user);
                    user.getChannelRights().insert(std::make_pair(this->_title, this->getModes())); // Insert user's channel rights
                }
                else
                {
                    if (this->userIsInvited(user.getNickname()))
                    {
                        this->_channelUsers.push_back(&user);
                        this->channelWelcome(user);
                        user.getChannelRights().insert(std::make_pair(this->_title, this->getModes()));// (?) what are the basic rights for a normal user
                        this->removeUserVector(this->getChannelInvited(), user.getNickname());
                    }
                    else
                        user.usr_send((ERR_INVITEONLYCHAN(user.getNickname(), this->getTitle())));
                }
            }
            else if (userIsBanned(user.getNickname()))
                user.usr_send((ERR_BANNEDFROMCHAN(user.getNickname(), this->getTitle())));
        }
    }
    else
        user.usr_send((ERR_CHANNELISFULL(user.getNickname(), this->getTitle())));
}

void Channel::removeUserVector(std::vector<User *> &vector, const std::string &name)
{
    std::vector<User *> temp;

    // Copy users that don't match the name to keep them
    for (std::vector<User *>::iterator it = vector.begin(); it != vector.end(); ++it)
    {
        if ((*it)->getNickname() != name)
            temp.push_back(*it);
    }
    // Assign the temporary vector back to the original one
    vector = temp;
}