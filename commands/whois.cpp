/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:15:09 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/29 10:18:19 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

void					whois(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)server;
    (void)params;
    user.usr_send("318 " + user.getUsername() + " " + user.getNickname() + " :END of /WHOIS list\r\n");
}