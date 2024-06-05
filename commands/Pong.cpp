/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:15:05 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/05 09:11:14 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

void					pong(User &user, SocketServer &server, std::vector<std::string> &params)
{
    (void)server;
    (void)params;
    user.usr_send("PING " + params.front() + "\r\n");
}
