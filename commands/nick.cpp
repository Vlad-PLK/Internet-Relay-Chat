/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:14:57 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/29 10:17:03 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

void					nick(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)server;
    std::string answer;
    user.setNickname(params.front());
    if (user.getCurrentState() == REJECTED)
    {
        answer = ERR_PASSWDMISMATCH(user.getNickname());
        send(user.getFD(), answer.c_str(), answer.size(), MSG_DONTWAIT | MSG_NOSIGNAL);
        //send(user.getFD(), "ERROR: incorrect password\r\n", 28, MSG_DONTWAIT | MSG_NOSIGNAL);
    }
}