#include "../SocketServer.hpp"

void    SocketServer::invite(User &user, std::vector<std::string> params)
{
    if (params.size() < 2)
    {
        user.usr_send((ERR_NEEDMOREPARAMS(user.getNickname(), "INVITE")));
        return;
    }
    
    std::string user_target = params[0];
    std::string channel_title = params[1];

    if (!this->findChannel(channel_title))
    {
        user.usr_send((ERR_NOSUCHCHANNEL(user.getNickname(), channel_title)));
        return;
    }
    Channel *channel = this->getChannel(channel_title);

    if (!channel->userIsMember(user.getNickname()) && !channel->userIsOperator(user.getNickname()))
        user.usr_send((ERR_NOTONCHANNEL(user.getNickname(), channel->getTitle())));
    else if (!channel->userIsOperator(user.getNickname()) && channel->getModes().find('i'))
        user.usr_send((ERR_CHANOPRIVSNEEDED(user.getNickname(), channel->getTitle())));
    else if (channel->userIsMember(user_target) || channel->userIsOperator(user_target)) // can a normal user have the +i to invite ?
        user.usr_send((ERR_USERONCHANNEL(user.getNickname(), user_target, channel_title)));
    else
    {
        channel->addInvited(user);
        user.usr_send((RPL_INVITING(user.getNickname(), user_target, channel_title)));
        this->getUser(user_target)->usr_send((RPL_INVITE(user.getNickname(), user_target, channel_title)));
    }
}