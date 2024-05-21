/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:10:43 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/21 11:17:19 by vpolojie         ###   ########.fr       */
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
    size_t      min_arg;
    size_t      max_arg;
public: 
    Command();
    ~Command();
    static const Command cmds[];
    void                      parseCommand(std::string &buffer);
    std::string const         &getRawCommand(void);
    std::vector<std::string> &getParams(void);
    std::string const         &getCmd(void);
    void                      setRawCommand(std::string &cmd);
    void                      setCmdName();
    void                      setCmdParams();
};

#endif