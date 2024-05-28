/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:10:43 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/27 11:10:18 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "SocketServer.hpp"
#include "User.hpp"
#include "Channel.hpp"

class User;
class Channel;
class SocketServer;

class Command
{
private:
    std::string raw_command;
    std::string cmd_name;
    std::vector<std::string> params;
public: 
    Command();
    ~Command();
    static const Command cmds[];
    void                      parseCommand(std::string &buffer);
    std::string const         &getRawCommand(void);
    std::vector<std::string> &getParams(void);
    std::string const         &getCmdName(void);
    void                      setRawCommand(std::string &cmd);
    void                      setCmdName();
    void                      setCmdParams();
    void                      clearCmd();
};

void					cap(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params);
void					pass(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params);
void					nick(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params);
void					user(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params);

#endif