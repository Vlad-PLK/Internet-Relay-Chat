/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:58:42 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/17 12:29:42 by vpolojie         ###   ########.fr       */
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

void    privmsg(User &user, SocketServer &server, std::vector<std::string> &params)
{
    std::vector<Channel *>::iterator    it;
    std::vector<User *>::iterator       itUs;
    std::string                         target;
    std::string                         msg_content;

    if (user.getNickname().empty() == true)
    {
        user.usr_send(ERR_NOTREGISTERED(std::string("*")));
        return ;
    }
    if (params.size() == 0)
    {
        user.usr_send(ERR_NORECIPIENT(user.getNickname()));
        return ;
    }
    else if (params[0].size() > 0 && params.size() == 1)
    {
        user.usr_send(ERR_NOTEXTTOSEND(user.getNickname()));
        return ;
    }

    target = params[0];
    if (params.size() > 1)
    {
        for (unsigned int i = 1; i < params.size(); i++)
            msg_content += params[i] + ' ';
        msg_content.erase(msg_content.length() - 1, 1);
    }
    
    if (target[0] == '#')
    {
        if (find_channel(server, target) == 0)
        {
            if (server.getChannel(target)->userIsMember(user.getNickname()) == false)
            {
                user.usr_send(ERR_USERNOTINCHANNEL(user.getNickname(), target));
                return ;
            }
            for (itUs = server.getChannel(target)->getChannelUsers().begin(); itUs != server.getChannel(target)->getChannelUsers().end(); itUs++)
            {
                if ((*itUs)->getNickname() != user.getNickname())
                    (*itUs)->usr_send(RPL_PRIVMSG(user.getNickname(), user.getUsername(), user.getIp(), target, msg_content));
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
}