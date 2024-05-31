#include "../Command.hpp"

void    mode(User &user, Channel &channel_void, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel_void;
    (void)server;
    if (params.size() < 2)
    {
        user.usr_send((ERR_NEEDMOREPARAMS(user.getNickname(), "MODE")).c_str());
        return ;
    }

    

}