#include "../SocketServer.hpp"

void SocketServer::join(User &user, std::vector<std::string> params)
{
    (void)channel;
    if (params.empty())
        user.usr_send((ERR_NEEDMOREPARAMS(user.getNickname(), "JOIN")));
    {
        user.my_send((ERR_NEEDMOREPARAMS(user.getNickname(), "JOIN")).c_str());
        return ;
    }
    
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
        if (!findChannel(channels[i]))
        {
            if (j < (int)passwords.size())
            {
                if (!passwords[j].empty())
                {
                    addChannel(channels[i], passwords[j]);
                    getChannel(channels[i])->addUser(user);
                }
                else
                {
                    addChannel(channels[i]);
                    getChannel(channels[i])->addUser(user);
                }
                ++j;
            }
            else
            {
                // if less passwords than channel names
                this->addChannel(channels[i]); 
                this->getChannel(channels[i])->addUser(user);
            }
        }
        else
        {
            if (!this->getChannel(channels[i])->getPassword().empty())
            {
                if (this->getChannel(channels[i])->getPassword() == passwords[j])
                    this->getChannel(channels[i])->addUser(user);
                else
                    user.usr_send((ERR_BADCHANNELKEY(user.getNickname(), this->getChannel(channels[i])->getTitle())).c_str());
            }
            // else if (this->getChannel(channels[i])->getPassword().empty() && !passwords[j].empty())
            //     user.my_send((ERR_BADCHANNELKEY(user.getNickname(), this->getChannel(channels[i])->getTitle())).c_str());
            ++j;
        }
    }
}