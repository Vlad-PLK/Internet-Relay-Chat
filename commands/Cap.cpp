/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:14:52 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/14 22:29:31 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

void					cap(User &user, SocketServer &server, std::vector<std::string> &params)
{
    (void)server;
    if (params.size() == 0)
        user.usr_send("\nINCOMPLETE REQUEST NEED : CAP LS\r\n");
    else if (params.size() == 1 && params[0] == "LS")
        user.setCurrentState(WAITING_FOR_APPROVAL);
    else
        user.usr_send("\nINCORRECT REQUEST NEED : CAP LS\r\n");
}