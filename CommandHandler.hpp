/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:12:40 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/21 11:16:36 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP
#include "SocketServer.hpp"
#include "User.hpp"
#include "Channel.hpp"

struct Command_Dictionnary{
    std::string name;
    void (SocketServer::*fct)(User &, Channel &, std::vector<std::string>);
};

static const Command_Dictionnary cmds[] {
    {"CAP LS", SocketServer::join},
};

#endif