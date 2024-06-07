#include "../Command.hpp"

void    join(User &user, SocketServer &server, std::vector<std::string> &params)
{
    // not params == error //
    if (params.empty())
    {
        user.usr_send((ERR_NEEDMOREPARAMS(user.getNickname(), "JOIN")));
        return ;
    }

    //MAYBE NEED TO USE PART HERE

    // Setting up the channel_titles vector to store all the names given in the command
    std::vector<std::string> channels = splitSetter(params[0]);
    // Setting up the channel_passwords vector 
    std::vector<std::string> passwords;
    if (params.size() > 1)
        passwords = splitSetter(params[1]);

    for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        if (!it->empty() && (*it)[0] != '#')
            it->insert(0, 1, '#'); // adds # as first character of the nickname
    }
    int i = -1;
    int j = 0;
    while (++i < (int)channels.size())
    {
        // if channel doesn't exists yet //
        if (!server.findChannel(channels[i]))
        {
            // if there are still passwords for channels
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
                //std::cout << server.getChannel(channels[i]) << std::endl;
                server.getChannel(channels[i])->addUser(user);
            }
        }
        // if channel already exists //
        else
        {
            Channel *channel = server.getChannel(channels[i]);
            if (!channel->getPassword().empty())
            {
               if (channel->getPassword() == passwords[j])
                   channel->addUser(user);
               else
                   user.usr_send((ERR_BADCHANNELKEY(user.getNickname(), channel->getTitle())));
            }
            if (channel->getPassword().empty())
                channel->addUser(user);
                //std::cout << "adding current user to existing channel : " << user.getNickname() << server.getChannel(channels[i])->getTitle() << std::endl;
            else if (channel->getPassword().empty() && !passwords[j].empty())
                user.usr_send((ERR_BADCHANNELKEY(user.getNickname(), channel->getTitle())));
            ++j;
        }
    }
}