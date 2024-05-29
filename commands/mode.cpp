#include "../SocketServer.hpp"

void    SocketServer::mode(User &user, std::vector<std::string> params)
{
    if (params.size() < 2)
    {
        user.my_send((ERR_NEEDMOREPARAMS(user.getNickname(), "MODE")).c_str());
        return ;
    }

    

}