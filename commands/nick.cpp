/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:14:57 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/29 12:21:26 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

int check_nickname_in_use(const std::string &nick, const std::vector<User> &users)
{
    for (size_t i = 0; i != users.size(); i++)
    {
        // NEED TO FIX IT WITH SERVER PART //
        if (nick == users[i].getNickname())
            return (1);
    }
    return (0);
}

int check_nickname_validity(const std::string &nick)
{
    if (nick.find("#") != std::string::npos 
        || nick.find(":") != std::string::npos 
        || nick.find(" ") != std::string::npos
        || nick.find("&") != std::string::npos)
    {
        return (1);
    }
    return (0);
}

void					nick(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)server;
    if (check_nickname_in_use(params.front(), server.getAllUsers()) == 1)
        user.usr_send(ERR_NICKNAMEINUSE(params.front()));
    else if (check_nickname_validity(params.front()) == 1)
        user.usr_send(ERR_ERRONEUSNICKNAME(params.front()));
    else if (params.front().size() == 0)
        user.usr_send(ERR_NONICKNAMEGIVEN());
    else
        user.setNickname(params.front());
    if (user.getCurrentState() == REJECTED)
        user.usr_send(ERR_PASSWDMISMATCH(user.getNickname()));
}