/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:14:55 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/29 10:18:37 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

void					mode(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)server;
    (void)params;
    std::string answer;
    user.usr_send("221 " + user.getNickname() + " +i\r\n");
}
