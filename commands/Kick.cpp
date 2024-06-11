#include "../Command.hpp"

void    kick(User &user, SocketServer &server, std::vector<std::string> &params)
{
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
    else if (!server.getChannel(channel_title)->userIsMember(user.getNickname()))
        user.usr_send((ERR_NOTONCHANNEL(user.getNickname(), server.getChannel(channel_title)->getTitle())));
    else
    {
        Channel *channel = server.getChannel(channel_title);
        if (channel->userIsOperator(user.getNickname()))
        {
            std::vector<std::string> users = splitSetter(params[1]);

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
                    User *kicked_user = server.getUser((*it));
                    kicked_user->usr_send(RPL_KICK((user.getNickname() + "!" + user.getUsername() + "@localhost"), channel->getTitle(), kicked_user->getNickname(), comment));
                    for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
                            (*itUser)->usr_send((RPL_KICK((user.getNickname() + "!" + user.getUsername() + "@localhost"), channel->getTitle(), *it, comment)));
                    std::cout << (kicked_user->getNickname()) << std::endl;
                    channel->deleteUser(kicked_user->getNickname());
                    if (channel->userIsOperator(kicked_user->getNickname()))
                        channel->deleteOperator(kicked_user->getNickname());
                }
            }
        }
        else
            user.usr_send((ERR_CHANOPRIVSNEEDED(user.getNickname(), channel->getTitle())));
    }
}