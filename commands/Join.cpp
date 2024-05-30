/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_bis.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:18:47 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/29 10:19:10 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

std::vector<std::string>    joinSetters(std::string param)
{
    std::vector<std::string> res;
    std::stringstream ss(param); // Use stringstream to split the string
    std::string copy;
    while (std::getline(ss, copy, ','))
        res.push_back(copy);
    return res;
}

void                    Join(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    if (params.empty())
    {
        user.usr_send((ERR_NEEDMOREPARAMS(user.getNickname(), "JOIN")).c_str());
        return ;
    }

    // Setting up the channel_titles vector to store all the names given in the command
    std::vector<std::string> channels = joinSetters(params[0]);
    
    std::vector<std::string> passwords;
    if (params.size() > 1)
        passwords = joinSetters(params[1]);

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
            if (!server.getChannel(channels[i])->getPassword().empty())
            {
                if (server.getChannel(channels[i])->getPassword() == passwords[j])
                    server.getChannel(channels[i])->addUser(user);
                else
                    user.usr_send((ERR_BADCHANNELKEY(user.getNickname(), server.getChannel(channels[i])->getTitle())));
            }
            // else if (this->getChannel(channels[i])->getPassword().empty() && !passwords[j].empty())
            //     user.usr_send((ERR_BADCHANNELKEY(user.getNickname(), this->getChannel(channels[i])->getTitle())).c_str());
            ++j;
        }
    }
}