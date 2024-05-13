/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:10:43 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/13 11:11:33 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "SocketServer.hpp"
#include "User.hpp"
#include "Chanel.hpp"

class Command
{
private:
    std::string raw_command;
    std::vector<std::string> params;

public: 
    void                      parseCommand(std::string &buffer);
    std::string              &getRawCommand(void);
    std::vector<std::string> &getParams(void);
    void                      setRawCommand(std::string &cmd);
};

#endif