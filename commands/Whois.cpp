/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:15:09 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/04 10:15:43 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

int check_nickname_in_use_whois(std::string &nick, const std::vector<User *> &users)
{
    for (size_t i = 0; i != users.size(); i++)
	{
        if (nick == users[i]->getNickname())
            return (1);
    }
    return (0);
}

void					whois(User &user, SocketServer &server, std::vector<std::string> &params)
{
    if (params.size() == 0 || params[0].size() == 0)
        user.usr_send(ERR_NONICKNAMEGIVEN());
    else if (check_nickname_in_use_whois(params[0], server.getAllUsers()) == 0)
        user.usr_send(ERR_NOSUCHNICK(params[0], "*"));
    user.usr_send("307 " + user.getNickname() + " " + user.getNickname() + " :has identified for this nick\r\n");
    user.usr_send("311 " + user.getNickname() + " " + user.getNickname() + " " + user.getUsername() + " " + user.getIp() + " * :" + user.getRealname() + "\r\n");
    user.usr_send("318 " + user.getNickname() + " " + user.getNickname() + " :END of /WHOIS list.\r\n");
}