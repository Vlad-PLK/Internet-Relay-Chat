/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:22:59 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/12 09:43:51 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

void quit(User &user, SocketServer &server, std::vector<std::string> &params)
{
	std::vector<Channel *>::iterator chanIt;
	std::vector<User *>::iterator userIt;
	for (chanIt = server.getAllChannels().begin(); chanIt != server.getAllChannels().end(); chanIt++)
	{
		if ((*chanIt)->userIsMember(user.getNickname()) == true)
		{
			for (userIt = (*chanIt)->getChannelUsers().begin(); userIt != (*chanIt)->getChannelUsers().end(); userIt++)
			{
				if (user.getNickname() != (*userIt)->getNickname())
				{
					if (params.size() > 0)
						(*userIt)->usr_send(RPL_QUIT(user.getNickname(), user.getUsername(), user.getIp(), params[0]));
					else
						(*userIt)->usr_send(RPL_QUIT(user.getNickname(), user.getUsername(), user.getIp(), "has quit"));
				}
			}
			(*chanIt)->deleteUser(user.getNickname());
			if ((*chanIt)->userIsOperator(user.getNickname()) == true)
			{
				(*chanIt)->deleteOperator(user.getNickname());
				if ((*chanIt)->getChannelOperators().size() == 0)
                	(*chanIt)->setOperators(*(*chanIt)->getChannelUsers().front(), true);
			}
			if ((*chanIt)->getChannelUsers().empty() == true)
				server.deleteChannel((*chanIt)->getTitle());
			else if ((*chanIt)->getChannelUsers().size() == 1 && (*chanIt)->getChannelOperators().size() == 0)
                (*chanIt)->setOperators(*(*chanIt)->getChannelUsers().front(), true);
			
			
		}
	}
	user.usr_send(RPL_QUIT(user.getNickname(), user.getUsername(), user.getIp(), "has quit"));
	close(user.getFD());
	delete server.getUser(user.getNickname());
}
