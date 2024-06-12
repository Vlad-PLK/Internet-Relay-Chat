/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:22:59 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/12 19:44:36 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

 void quit(User &user, SocketServer &server, std::vector<std::string> &params)
{
    std::vector<Channel *> channelsToDelete;
    std::vector<User *>::iterator userIt;

 	std::string reason;
 	if (params.size() > 1)
 	{
 		for (size_t i = 1; i < params.size(); i++)
 	  		reason += params[i] + ' ';
 	 	reason.erase(reason.length() - 1, 1);
 	}
 	else
 	 	reason = "has quit";
    
    for (std::vector<Channel *>::iterator chanIt = server.getAllChannels().begin(); chanIt != server.getAllChannels().end(); chanIt++)
    {
        Channel *channel = *chanIt;
        if (channel->userIsMember(user.getNickname()))
        {
            for (userIt = channel->getChannelUsers().begin(); userIt != channel->getChannelUsers().end(); userIt++)
            {
                User *channelUser = *userIt;
                if (channelUser != &user)
                    channelUser->usr_send(RPL_QUIT(user.getNickname(), user.getUsername(), user.getIp(), reason));
            }

            channel->deleteUser(user.getNickname());
            if (channel->userIsOperator(user.getNickname()))
            {
                channel->deleteOperator(user.getNickname());
                if (channel->getChannelOperators().empty() && !channel->getChannelUsers().empty())
                    channel->setOperators(*channel->getChannelUsers().front(), true);
            }

            if (channel->getChannelUsers().empty())
                channelsToDelete.push_back(channel);
            else if (channel->getChannelUsers().size() == 1 && channel->getChannelOperators().empty())
                channel->setOperators(*channel->getChannelUsers().front(), true);
        }
    }

    // Delete empty channels
    for (size_t i = 0; i < channelsToDelete.size(); i++)
        server.deleteChannel(channelsToDelete[i]->getTitle());

    // Close the user's connection and delete the user from the server
    close(user.getFD());
    server.deleteUser(user.getNickname());
}
