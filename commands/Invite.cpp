#include "../SocketServer.hpp"

void    SocketServer::invite(User &user, std::vector<std::string> params)
{
    if (params.size() < 2)
    {
        user.my_send((ERR_NEEDMOREPARAMS(user.getNickname(), "INVITE")).c_str());
        return;
    }
    
    std::string user_target = params[0];
    std::string channel_title = params[1];

    if (!this->findChannel(channel_title))
    {
        user.my_send((ERR_NOSUCHCHANNEL(user.getNickname(), channel_title)).c_str());
        return;
    }
    Channel *channel = this->getChannel(channel_title);

    if (!channel->userIsMember(user.getNickname()) && !channel->userIsOperator(user.getNickname()))
        user.my_send((ERR_NOTONCHANNEL(user.getNickname(), channel->getTitle())).c_str());
    else if (!channel->userIsOperator(user.getNickname()) && channel->getModes().find('i'))
        user.my_send((ERR_CHANOPRIVSNEEDED(user.getNickname(), channel->getTitle())).c_str());
    else if (channel->userIsMember(user_target) || channel->userIsOperator(user_target)) // can a normal user have the +i to invite ?
        user.my_send((ERR_USERONCHANNEL(user.getNickname(), user_target, channel_title)).c_str());
    else
    {
        channel->addInvited(user);
        user.my_send((RPL_INVITING(user.getNickname(), user_target, channel_title)).c_str());
        this->getUser(user_target)->my_send((RPL_INVITE(user.getNickname(), user_target, channel_title)).c_str());
    }
}