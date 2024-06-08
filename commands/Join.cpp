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
    int i = 0;
    int j = 0;
    while (i < (int)channels.size())
    {
        // if channel doesn't exist yet
        if (!server.findChannel(channels[i]))
        {
            // if there are still passwords for channels
            if (j < (int)passwords.size())
            {
                if (!passwords[j].empty() && !channels[i].empty())
                {
                    std::cout << "\nNEW CHANNEL password :" << passwords[j] << std::endl;
                    server.addChannel(channels[i], passwords[j]);
                    server.getChannel(channels[i])->addUser(user);
                    ++j;  // Increment j only when a password is used
                }
                else
                {
                    if (!channels[i].empty())
                    {
                        std::cout << "\nNEW CHANNEL NO password" << std::endl;
                        server.addChannel(channels[i]);
                        server.getChannel(channels[i])->addUser(user);
                    }
                }
            }
            else
            {
                // if less passwords than channel names
                if (!channels[i].empty())
                {
                    server.addChannel(channels[i]);
                    server.getChannel(channels[i])->addUser(user);
                }
            }
        }
        // if channel already exists
        else
        {
            Channel *channel = server.getChannel(channels[i]);
            if (!channel->getPassword().empty())
            {
                if (channel->getModes().find('i') != std::string::npos && channel->userIsInvited(user.getNickname()))
                {
                    channel->addUser(user);
                    ++j;
                }
                else if (j < (int)passwords.size() && !passwords[j].empty() && channel->getPassword() == passwords[j])
                {
                    std::cout << "\nCHANNEL password :" << channel->getPassword() << "|| CMD password :" << passwords[j] << std::endl;
                    channel->addUser(user);
                    ++j;  // Increment j only when a password is used
                }
                else
                {
                    if (channel->getModes().find('i') != std::string::npos && !channel->userIsInvited(user.getNickname()))
                        user.usr_send((ERR_INVITEONLYCHAN(user.getNickname(), channel->getTitle())));
                    else
                        user.usr_send(ERR_BADCHANNELKEY(user.getNickname(), channel->getTitle()));
                }
            }
            else
                channel->addUser(user);
            // Uncomment and handle the case if required
            // else if (channel->getPassword().empty() && !passwords[j].empty())
            //     user.usr_send((ERR_BADCHANNELKEY(user.getNickname(), channel->getTitle())));
        }
        ++i;
    }
}

//NEED TO make the tests for JOIN multiple channels with/without passwords etc...

