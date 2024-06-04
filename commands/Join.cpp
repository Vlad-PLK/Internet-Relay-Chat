#include "../Command.hpp"

void    join(User &user, Channel &channel_void, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel_void;
    if (params.empty())
    {
        user.usr_send((ERR_NEEDMOREPARAMS(user.getNickname(), "JOIN")).c_str());
        return ;
    }

    //MAYBE NEED TO USE PART HERE

    // Setting up the channel_titles vector to store all the names given in the command
    std::vector<std::string> channels = splitSetter(params[0]);
    
    std::vector<std::string> passwords;
    if (params.size() > 1)
        passwords = splitSetter(params[1]);

    // Creating non existing channels
    for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        if (!it->empty() && (*it)[0] != '#')
            it->insert(0, 1, '#'); // adds # as first character of the nickname
    }
    int i = -1;
    int j = 0;
    while (++i < (int)channels.size())
    {
        if (!server.findChannel(channels[i]))
        {
            if (j < (int)passwords.size())
            {
                if (!passwords[j].empty())
                {
                    server.addChannel(channels[i], passwords[j]);
                    server.getChannel(channels[i])->addUser(user);
                }
                else
                {
                    server.addChannel(channels[i]);
                    server.getChannel(channels[i])->addUser(user);
                }
                ++j;
            }
            else
            {
                // if less passwords than channel names
                server.addChannel(channels[i]); 
                server.getChannel(channels[i])->addUser(user);
            }
        }
        else
        {
            Channel *channel = server.getChannel(channels[i]);
            if (!channel->getPassword().empty())
            {
                if (channel->getPassword() == passwords[j])
                    channel->addUser(user);
                else
                    user.usr_send((ERR_BADCHANNELKEY(user.getNickname(), channel->getTitle())).c_str());
            }
            // else if (this->getChannel(channels[i])->getPassword().empty() && !passwords[j].empty())
            //     user.usr_send((ERR_BADCHANNELKEY(user.getNickname(), this->getChannel(channels[i])->getTitle())).c_str());
            ++j;
        }
    }
}