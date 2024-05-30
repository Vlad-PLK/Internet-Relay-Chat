#include "../SocketServer.hpp"

void    SocketServer::topic(User &user, std::vector<std::string> params)
{
    if (params.empty())
    {
        user.usr_send((ERR_NEEDMOREPARAMS(user.getNickname(), "TOPIC")));
        return ;
    }

    std::string channel_title = params[0];
    // if (channel_title[0] != '#')
    //         channel_title.insert(0, 1, '#');
    if (!findChannel(channel_title))
        user.usr_send((ERR_NOSUCHCHANNEL(user.getNickname(), channel_title)));
    else if (!this->getChannel(channel_title)->userIsMember(user.getNickname()) && !this->getChannel(channel_title)->userIsOperator(user.getNickname()))
        user.usr_send((ERR_NOTONCHANNEL(user.getNickname(), this->getChannel(channel_title)->getTitle())));
    else
    {
        Channel *channel = this->getChannel(channel_title);
        if (params.size() == 1)
        {
            if (channel->getTopic() == "")
                user.usr_send((RPL_NOTOPIC(user.getNickname(), channel->getTitle())));
            else
                user.usr_send((RPL_TOPIC(user.getNickname(), channel->getTitle(), channel->getTopic())));
        }
        else
        {
            if (channel->getModes().find('t') && !channel->userIsOperator(user.getNickname()))
                user.usr_send((ERR_CHANOPRIVSNEEDED(user.getNickname(), channel->getTitle())));
            else
            {
                std::string topic;
                for (int i = 1; i < (int)params.size(); i++)
                    topic += params[i] + ' ';
                topic.erase(topic.length() - 1, 1);
                channel->setTopic(topic);
                for (std::vector<User>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
                    itUser->usr_send((RPL_TOPIC(itUser->getNickname(), channel->getTitle(), channel->getTopic())));
                for (std::vector<User>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
                    itOp->usr_send((RPL_TOPIC(itOp->getNickname(), channel->getTitle(), channel->getTopic())));
            }
        }
    }
}