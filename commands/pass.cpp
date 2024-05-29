/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:15:00 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/29 10:16:33 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

void					pass(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    if (server.getPassword() == params.front())
        user.setCurrentState(ACCEPTED);
    else
        user.setCurrentState(REJECTED);
}
