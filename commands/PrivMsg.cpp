/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:58:42 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/11 09:56:21 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

int find_channel(SocketServer &server, std::string target)
{
    std::vector<Channel *>::iterator    it;
    for (it = server.getAllChannels().begin(); it != server.getAllChannels().end(); it++)
    {
        if ((*it)->getTitle() == target)
            return (0);
    }
    return (1);
}

int find_user(SocketServer &server, std::string target)
{
    std::vector<User *>::iterator    it;
    for (it = server.getAllUsers().begin(); it != server.getAllUsers().end(); it++)
    {
        if ((*it)->getNickname() == target)
            return (0);
    }
    return (1);
}

void                    privmsg(User &user, SocketServer &server, std::vector<std::string> &params)
{
    std::vector<Channel *>::iterator    it;
    std::vector<User *>::iterator       itUs;
    std::string                         target;
    std::string                         msg_content;

    if (params[0].size() > 0 && params[1].size() > 0)
    {
        target = params[0];
        msg_content = params[1];
    }
    else
        user.usr_send(ERR_NEEDMOREPARAMS(user.getNickname(), "PRIVMSG"));

    if (target[0] == '#')
    {
        if (find_channel(server, target) == 0)
        {
            for (it = server.getAllChannels().begin(); it != server.getAllChannels().end(); it++)
            {
                if ((*it)->getTitle() == target)
                {
                    for (itUs = server.getChannel(target)->getChannelUsers().begin(); itUs != server.getChannel(target)->getChannelUsers().end(); itUs++)
                    {
                        if ((*itUs)->getNickname() != user.getNickname())
                            (*itUs)->usr_send(RPL_PRIVMSG(user.getNickname(), user.getUsername(), user.getIp(), target, msg_content));
                    }
                }
            }
        }
        else
            user.usr_send(ERR_NOSUCHCHANNEL(user.getNickname(), target));
    }
    else 
    {
        if (find_user(server, target) == 0)
        {
            for (itUs = server.getAllUsers().begin(); itUs != server.getAllUsers().end(); itUs++)
            {
                if ((*itUs)->getNickname() == target)
                    (*itUs)->usr_send(RPL_PRIVMSG(user.getNickname(), user.getUsername(), user.getIp(), target, msg_content));
            }
        }
        else
            user.usr_send(ERR_NOSUCHNICK(user.getNickname(), target));
    }

    // if <target> == user //
        //send to user//
        /// if user is away -> reply with RPL_AWAY(310)
    // if <target> == channel //
        //send to channel
        // check banned users//
        // ERR_CANNOTSENDTOCHAN //
}