#include "../SocketServer.hpp"

void    SocketServer::kick(User &user, std::vector<std::string> params)
{
    if (params.size() < 2)
    {
        user.my_send((ERR_NEEDMOREPARAMS(user.getNickname(), "KICK")).c_str());
        return ;
    }
    std::string channel_title = params[0];
    // if (channel_title[0] != '#'  channel_title[0] != '@')
    // //         channel_title.insert(0, 1, '#');
    if (!findChannel(channel_title))
        user.my_send((ERR_NOSUCHCHANNEL(user.getNickname(), channel_title)).c_str());
    else if (!this->getChannel(channel_title)->userIsMember(user.getNickname()) && !this->getChannel(channel_title)->userIsOperator(user.getNickname()) && !this->getChannel(channel_title)->userIsOperator('@' + user.getNickname()))
        user.my_send((ERR_NOTONCHANNEL(user.getNickname(), this->getChannel(channel_title)->getTitle())).c_str());
    else if (this->getChannel(channel_title)->userIsMember(user.getNickname()) && !this->getChannel(channel_title)->userIsOperator(user.getNickname()) && !this->getChannel(channel_title)->userIsOperator('@' + user.getNickname()))
        user.my_send((ERR_CHANOPRIVSNEEDED(user.getNickname(), this->getChannel(channel_title)->getTitle())).c_str());

    std::vector<std::string> users = splitSetter(params[1]);
    Channel *channel = this->getChannel(channel_title);

    for (std::vector<std::string>::iterator it = users.begin(); it != users.end(); ++it)
    {
        if (!channel->userIsMember(*it) && !channel->userIsOperator(*it) && !channel->userIsOperator('@' + *it))
            user.my_send((ERR_USERNOTINCHANNEL(*it, channel->getTitle())).c_str());
        else
        {
            std::string comment;
            if (!params[2].empty())
            {
                for (int i = 2; i < (int)params.size(); i++)
                    comment += params[i] + ' ';
            }
            for (std::vector<User>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
                    itUser->my_send((RPL_KICK((user.getNickname() + "!" + user.getUsername() + "@localhost"), channel->getTitle(), *it, comment)).c_str());
            for (std::vector<User>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
                    itOp->my_send((RPL_KICK((user.getNickname() + "!" + user.getUsername() + "@localhost"), channel->getTitle(), *it, comment)).c_str());
            if (channel->userIsMember(*it))
                channel->deleteUser(*it);
            else
                channel->deleteOperator(*it);
        }
    }
}