#include "../Command.hpp"

void    topic(User &user, SocketServer &server, std::vector<std::string> &params)
{
    if (params.empty())
    {
        user.usr_send((ERR_NEEDMOREPARAMS(user.getNickname(), "TOPIC")));
        return ;
    }

    std::string channel_title = params[0];
    if (!server.findChannel(channel_title))
        user.usr_send((ERR_NOSUCHCHANNEL(user.getNickname(), channel_title)));
    else if (!server.getChannel(channel_title)->userIsMember(user.getNickname()) && !server.getChannel(channel_title)->userIsOperator(user.getNickname()))
        user.usr_send((ERR_NOTONCHANNEL(user.getNickname(), server.getChannel(channel_title)->getTitle())));
    else
    {
        Channel *channel = server.getChannel(channel_title);
        if (params.size() == 1)
        {
            if (channel->getTopic().empty())
                user.usr_send((RPL_NOTOPIC(user.getNickname(), channel->getTitle())));
            else
                user.usr_send((RPL_TOPIC(user.getNickname(), channel->getTitle(), channel->getTopic())));
        }
        else
        {
            if (channel->getModes().find('t') == std::string::npos || (channel->getModes().find('t') != std::string::npos && channel->userIsOperator(user.getNickname())))
            {
                std::string topic;
                for (int i = 1; i < (int)params.size(); i++)
                    topic += params[i] + ' ';
                topic.erase(topic.length() - 1, 1);
                if (topic != channel->getTopic())
                    channel->setTopic(topic);
                for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
                    (*itUser)->usr_send((RPL_TOPIC((*itUser)->getNickname(), channel->getTitle(), channel->getTopic())));
            }
            else
                user.usr_send((ERR_CHANOPRIVSNEEDED(user.getNickname(), channel->getTitle())));
        }
    }
}