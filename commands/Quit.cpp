/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:22:59 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/29 12:37:34 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

void quit(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
	(void)channel;
	(void)server;
	(void)params;
    user.usr_send("ERROR: connexion lost");
	//exit all channels//
	user.usr_clean();
	//if QUIT + reasom from clients, then send quit + reason to other clients //
	//if QUIT withouth beeing issued by the client, send quit + reason to other clients //
	close(user.getFD());
}
