/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:10:43 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/29 10:06:51 by vpolojie         ###   ########.fr       */
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
    void                      parseCommand(std::string &buffer);
    std::string const         &getRawCommand(void);
    std::vector<std::string> &getParams(void);
    std::string const         &getCmdName(void);
    void                      setRawCommand(std::string &cmd);
    void                      setCmdName();
    void                      setCmdParams();
    void                      clearCmd();
};

typedef struct S_Command_Dictionnary{
    std::string name;
    void (*fct)(User &, Channel &, SocketServer &, std::vector<std::string> &);
}Command_Dictionnary;


void HandleCommand(Command &cmd, User &usr, Channel &chl, SocketServer &server);

void					cap(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params);
void					pass(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params);
void					nick(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params);
void					user(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params);
void                    whois(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params);
void                    mode(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params);
void                    ping(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params);
void                    pong(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params);
void                    join_bis(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params);

#endif