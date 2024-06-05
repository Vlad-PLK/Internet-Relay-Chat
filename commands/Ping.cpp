/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:15:02 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/05 09:11:08 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

void					ping(User &user, SocketServer &server, std::vector<std::string> &params)
{
    (void)server;
    (void)params;
    user.usr_send("PONG " + params.front() + "\r\n");
}
