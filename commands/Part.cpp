#include "../Command.hpp"

void    part(User &user, SocketServer &server, std::vector<std::string> &params)
{
    if (params.empty())
    {
        user.usr_send((ERR_NEEDMOREPARAMS(user.getNickname(), "PART")));
        return ;
    }
    
    std::vector<std::string> channels = splitSetter(params[0]);

    for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        if (!it->empty() && (*it)[0] != '#')
            it->insert(0, 1, '#');
    }

    int i = -1;
    while (++i < (int)channels.size())
    {
        if (!server.findChannel(channels[i]))
            user.usr_send((ERR_NOSUCHCHANNEL(user.getNickname(), channels[i])));
        else
        {
            Channel *channel = server.getChannel(channels[i]);
            if (!channel->userIsMember(user.getNickname()))
                user.usr_send((ERR_NOTONCHANNEL(user.getNickname(), channel->getTitle())));
            else
            {
                std::string reason;
                if (params.size() > 1)
                {
                    for (size_t i = 1; i < params.size(); i++)
                        reason += params[i] + ' ';
                    reason.erase(reason.length() - 1, 1);
                }
                for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
                    (*itUser)->usr_send((RPL_PART(user.getNickname(), user.getUsername(), user.getIp(), channel->getTitle(), reason)));
                channel->deleteUser(user.getNickname());
                if (channel->userIsOperator(user.getNickname()) == true)
                {
                    channel->deleteOperator(user.getNickname());
                    if (channel->getChannelOperators().size() == 0)
                	    channel->setOperators(*channel->getChannelUsers().front(), true);
                }
                if (channel->getChannelUsers().size() == 1 && channel->getChannelOperators().empty() == true)
                {
                    User *only_user = channel->getChannelUsers().front();
                    channel->setOperators(*only_user, true);
                }
                else if (channel->getChannelUsers().size() == 0)
                   server.deleteChannel(channels[i]);
            }
        }
    }
}