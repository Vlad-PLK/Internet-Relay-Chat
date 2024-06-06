/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:58:42 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/06 11:20:51 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

void                    privmsg(User &user, SocketServer &server, std::vector<std::string> &params)
{
    std::vector<Channel *>::iterator it;
    std::vector<User *>::iterator itUs;
    for (it = server.getAllChannels().begin(); it != server.getAllChannels().end(); it++)
    {
        if ((*it)->getTitle() == params[0])
        {
            for (itUs = server.getChannel(params[0])->getChannelUsers().begin(); itUs != server.getChannel(params[0])->getChannelUsers().end(); itUs++)
            {
                if ((*itUs)->getNickname() != user.getNickname())
                    (*itUs)->usr_send(RPL_PRIVMSG((*itUs)->getNickname(), (*itUs)->getUsername(), (*itUs)->getIp(), params[0], params[1]));
            }
        }
    }
    // if <target> == user //
        //send to user//
        /// if user is away -> reply with RPL_AWAY(310)
    // if <target> == channel //
        //send to channel
        // check banned users//
        // ERR_CANNOTSENDTOCHAN //
}