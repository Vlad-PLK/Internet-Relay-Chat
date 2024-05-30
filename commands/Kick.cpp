#include "../SocketServer.hpp"
#include "../Command.hpp"

void    Kick(User &user, Channel &chl, SocketServer &server, std::vector<std::string> &params)
{
    (void)chl;
    if (params.size() < 2)
    {
        user.usr_send((ERR_NEEDMOREPARAMS(user.getNickname(), "KICK")));
        return ;
    }
    std::string channel_title = params[0];
    // if (channel_title[0] != '#'  channel_title[0] != '@')
    // //         channel_title.insert(0, 1, '#');
    if (!server.findChannel(channel_title))
        user.usr_send((ERR_NOSUCHCHANNEL(user.getNickname(), channel_title)));
    else if (!server.getChannel(channel_title)->userIsMember(user.getNickname()) && !server.getChannel(channel_title)->userIsOperator(user.getNickname()) && !server.getChannel(channel_title)->userIsOperator('@' + user.getNickname()))
        user.usr_send((ERR_NOTONCHANNEL(user.getNickname(), server.getChannel(channel_title)->getTitle())));
    else if (server.getChannel(channel_title)->userIsMember(user.getNickname()) && !server.getChannel(channel_title)->userIsOperator(user.getNickname()) && !server.getChannel(channel_title)->userIsOperator('@' + user.getNickname()))
        user.usr_send((ERR_CHANOPRIVSNEEDED(user.getNickname(), server.getChannel(channel_title)->getTitle())));

    std::vector<std::string> users = joinSetters(params[1]);
    Channel *channel = server.getChannel(channel_title);

    for (std::vector<std::string>::iterator it = users.begin(); it != users.end(); ++it)
    {
        if (!channel->userIsMember(*it) && !channel->userIsOperator(*it) && !channel->userIsOperator('@' + *it))
            user.usr_send((ERR_USERNOTINCHANNEL(*it, channel->getTitle())));
        else
        {
            std::string comment;
            if (!params[2].empty())
            {
                for (int i = 2; i < (int)params.size(); i++)
                    comment += params[i] + ' ';
            }
            for (std::vector<User>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
                    itUser->usr_send((RPL_KICK((user.getNickname() + "!" + user.getUsername() + "@localhost"), channel->getTitle(), *it, comment)));
            for (std::vector<User>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
                    itOp->usr_send((RPL_KICK((user.getNickname() + "!" + user.getUsername() + "@localhost"), channel->getTitle(), *it, comment)));
            if (channel->userIsMember(*it))
                channel->deleteUser(*it);
            else
                channel->deleteOperator(*it);
        }
    }
}