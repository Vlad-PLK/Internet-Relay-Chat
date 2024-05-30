#include "../Command.hpp"
#include "../Server_comments.hpp"

void    mode(User &user, Channel &channel, SocketServer &server, std::vector<std::string> params)
{
    (void)channel;
    (void)server;
    if (params.size() < 2)
    {
        user.usr_send((ERR_NEEDMOREPARAMS(user.getNickname(), "MODE")));
        return ;
    }
}