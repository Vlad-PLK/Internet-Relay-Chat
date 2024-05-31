#include "../Command.hpp"

void    part(User &user, Channel &channel_void, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel_void;
    if (params.empty())
    {
        user.usr_send((ERR_NEEDMOREPARAMS(user.getNickname(), "PART")).c_str());
        return ;
    }
    
    std::vector<std::string> channels = joinSetters(params[0]);

    // for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
    // {
    //     if (!it->empty() && (*it)[0] != '#')
    //         it->insert(0, 1, '#');
    // }

    int i = -1;
    while (++i < (int)channels.size())
    {
        if (!server.findChannel(channels[i]))
            user.usr_send((ERR_NOSUCHCHANNEL(user.getNickname(), channels[i])).c_str());
        else
        {
            if (!server.getChannel(channels[i])->userIsMember(user.getNickname()) && !server.getChannel(channels[i])->userIsMember(user.getNickname()))
                user.usr_send((ERR_NOTONCHANNEL(user.getNickname(), server.getChannel(channels[i])->getTitle())).c_str());
            else
            {
                std::string reason;
                if (params.size() > 1)
                {
                    for (size_t i = 1; i < params.size(); i++)
                        reason += params[i] + ' ';
                }
                user.usr_send((RPL_PART(user.getNickname(), server.getChannel(channels[i])->getTitle(), reason)).c_str());
                if (server.getChannel(channels[i])->userIsMember(user.getNickname()))   
                    server.getChannel(channels[i])->deleteUser(user.getNickname());
                else
                    server.getChannel(channels[i])->deleteOperator(user.getNickname());
                if (server.getChannel(channels[i])->getChannelUsers().size() + server.getChannel(channels[i])->getChannelOperators().size() == 0)
                    server.deleteChannel(channels[i]);
            }
        }
    }
}