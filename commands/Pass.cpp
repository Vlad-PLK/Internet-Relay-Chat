/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:15:00 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/03 13:25:37 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

void					pass(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    if (server.getPassword() == params.front())
        user.setCurrentState(ACCEPTED);
    else
    {
        params[0].assign("*");
        user.usr_send(ERR_PASSWDMISMATCH(params[0]));
        user.setCurrentState(REJECTED);
    }
}
