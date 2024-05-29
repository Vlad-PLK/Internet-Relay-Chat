/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:15:07 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/29 10:18:02 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

void					user(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)server;
    if (user.getCurrentState() == ACCEPTED)
    {
        user.setUsername(params.front());
        user.usr_send("001 " + user.getNickname() + " :Welcome to 42's Network " + user.getNickname() + "\r\n");
        user.usr_send("002 " + user.getNickname() + " :Your host is VPTV, running version lol.dev.c3plus\r\n");
        user.usr_send("003 " + user.getNickname() + " :This server was created 2024-05-28 10:11 CEST:+0200\r\n");
        user.usr_send("004 " + user.getNickname() + " VPTV version lol.dev.c3plus MODE : +/- itkol\r\n");
    }
}