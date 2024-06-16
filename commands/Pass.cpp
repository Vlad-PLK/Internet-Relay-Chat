/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:15:00 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/16 04:27:10 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

void					pass(User &user , SocketServer &server, std::vector<std::string> &params)
{
    std::string tmp = "*";
    if (user.getCurrentState() == WAITING_FOR_APPROVAL)
    {
        if (params.size() == 0)
            user.usr_send(ERR_NEEDMOREPARAMS(tmp, "PASS"));
        else if (params.size() == 1)
        {
            if (params[0] == server.getPassword())
                user.setCurrentState(ACCEPTED);
            else
            {
                params[0].assign("*");
                user.usr_send(ERR_PASSWDMISMATCH(params[0]));
            }
        }
        else if (params.size() > 1 && isNotSpace(params, 1) == 0)
        {
            if (params[0] == server.getPassword() && isNotSpace(params, 1) == 0)
                user.setCurrentState(ACCEPTED);
            else
            {
                params[0].assign("*");
                user.usr_send(ERR_PASSWDMISMATCH(params[0]));
            }
        }
        else
            user.usr_send("\nTOO MUCH PARAMS FOR PASS COMMAND, ONLY ALLOWED\r\n");
        
    }
    else
        user.usr_send("\nWAITING FOR CAP LS INTRODUCTION\r\n");
}
