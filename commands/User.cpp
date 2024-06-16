/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:15:07 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/16 07:03:53 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

void					user(User &user, SocketServer &server, std::vector<std::string> &params)
{
    (void)server;
    if (user.getCurrentState() == ACCEPTED && user.getNickname().empty() == false)
    {
        if (params.size() < 4)
            user.usr_send(ERR_NEEDMOREPARAMS(user.getNickname(), "USER"));
        else if (params.size() > 4 && isNotSpace(params, 3) == 1)
            user.usr_send("\nTOO MUCH PARAMS FOR USER COMMAND\r\n");
        else
        {
            user.setUsername(params[0]);
            user.setIp(params[2]);
            user.setRealname(params.back());
            user.usr_send("001 " + user.getNickname() + " :Welcome to 42's Network " + user.getNickname() + "\r\n");
            user.usr_send("002 " + user.getNickname() + " :Your host is VPTV, running version lol.dev.c3plus\r\n");
            user.usr_send("003 " + user.getNickname() + " :This server was created 2024-05-28 10:11 CEST:+0200\r\n");
            user.usr_send("004 " + user.getNickname() + " VPTV version lol.dev.c3plus MODE : +/- itkol\r\n");
            user.setCurrentState(ALREADY_REGISTRED);
        }
    }
    else if (user.getCurrentState() == ALREADY_REGISTRED)
        user.usr_send(ERR_ALREADYREGISTERED(user.getNickname()));
    else
        user.usr_send("\nWAITING FOR OTHER COMMANDS BEFORE FINISHING REGISTRATION\r\n");
}