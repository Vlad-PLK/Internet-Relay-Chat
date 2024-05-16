/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:10:43 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/13 16:32:35 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "SocketServer.hpp"
#include "User.hpp"
#include "Channel.hpp"

class Command
{
private:
    std::string raw_command;
    std::string cmd_name;
    std::vector<std::string> params;
public: 
    Command();
    ~Command();
    void                      parseCommand(std::string &buffer);
    std::string const         &getRawCommand(void);
    std::vector<std::string> &getParams(void);
    std::string const         &getCmd(void);
    void                      setRawCommand(std::string &cmd);
    void                      setCmdName();
    void                      setCmdParams();
};

#endif