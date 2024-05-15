#include "../SocketServer.hpp"

std::vector<std::string>    joinSetter(std::string param)
{
    std::vector<std::string> res;
    std::stringstream ss(param); // Use stringstream to split the string
    std::string copy;
    while (std::getline(ss, copy, ','))
        res.push_back(copy);
    return res;
}

void SocketServer::join(User &user, Channel &channel, std::vector<std::string> params)
{
    if (params.empty())
        user.my_send((ERR_NEEDMOREPARAMS(user.getNickname(), "JOIN")).c_str(), (ERR_NEEDMOREPARAMS(user.getNickname(), "JOIN")).length(), 0);
    
    // Setting up the channel_titles vector to store all the names given in the command
    std::vector<std::string> channels = joinSetter(params[0]);
    
    std::vector<std::string> passwords;
    if (params.size() > 1)
        passwords = joinSetter(params[1]);

    // Creating non existing channels
    for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        if (it->at(0) != '#')
            it->insert(0, 1, '#'); // adds # as first character of the nickname
    }
    size_t i = -1;
    size_t j = 0;
    while (++i < channels.size())
    {
        if (j < passwords.size())
        {
            if (!passwords[j].empty())
                addChannel(channels[i], passwords[j]);
            else
                addChannel(channels[i]);
            ++j;
        }
        else
            this->addChannel(channels[i]); // if less passwords than channel names
    }
}