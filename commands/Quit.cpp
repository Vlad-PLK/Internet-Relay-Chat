/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:22:59 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/12 12:03:45 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

void quit(User &user, SocketServer &server, std::vector<std::string> &params)
{
	(void)params;
	std::vector<Channel *>::iterator chanIt;
	std::vector<User *>::iterator userIt;
	std::string tmp_nickname = user.getNickname();
	for (chanIt = server.getAllChannels().begin(); chanIt != server.getAllChannels().end(); chanIt++)
	{
		if ((*chanIt)->userIsMember(tmp_nickname) == true)
		{
			//if ((*chanIt)->getChannelUsers().size() > 0)
			//{
			//	for (userIt = (*chanIt)->getChannelUsers().begin(); userIt != (*chanIt)->getChannelUsers().end(); userIt++)
			//	{
			//		if ((*userIt)->getNickname() != tmp_nickname)
			//			(*userIt)->usr_send(RPL_QUIT(user.getNickname(), user.getUsername(), user.getIp(), "has quit"));
			//	}
			//}
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
	close(user.getFD());
	delete server.getUser(user.getNickname());
}
