#include "../SocketServer.hpp"

void    SocketServer::part(User &user, std::vector<std::string> params)
{
    if (params.empty())
    {
        user.usr_send((ERR_NEEDMOREPARAMS(user.getNickname(), "PART")));
        return ;
    }
    
    std::vector<std::string> channels = splitSetter(params[0]);

    // for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
    // {
    //     if (!it->empty() && (*it)[0] != '#')
    //         it->insert(0, 1, '#');
    // }

    int i = -1;
    while (++i < (int)channels.size())
    {
        if (!findChannel(channels[i]))
            user.usr_send((ERR_NOSUCHCHANNEL(user.getNickname(), channels[i])));
        else
        {
            if (!this->getChannel(channels[i])->userIsMember(user.getNickname()) && !this->getChannel(channels[i])->userIsMember(user.getNickname()))
                user.usr_send((ERR_NOTONCHANNEL(user.getNickname(), this->getChannel(channels[i])->getTitle())));
            else
            {
                std::string reason;
                if (params.size() > 1)
                {
                    for (size_t i = 1; i < params.size(); i++)
                        reason += params[i] + ' ';
                }
                user.usr_send((RPL_PART(user.getNickname(), this->getChannel(channels[i])->getTitle(), reason)));
                if (this->getChannel(channels[i])->userIsMember(user.getNickname()))   
                    this->getChannel(channels[i])->deleteUser(user.getNickname());
                else
                    this->getChannel(channels[i])->deleteOperator(user.getNickname());
                if (this->getChannel(channels[i])->getChannelUsers().size() + this->getChannel(channels[i])->getChannelOperators().size() == 0)
                    this->deleteChannel(channels[i]);
            }
        }
    }
}