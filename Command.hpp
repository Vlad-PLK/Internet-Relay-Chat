/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:10:43 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/05 09:08:32 by vpolojie         ###   ########.fr       */
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
    void (*fct)(User &, SocketServer &, std::vector<std::string> &);
}Command_Dictionnary;

int check_nickname_in_use(std::string &nick, const std::vector<User *> &users);
void HandleCommand(Command &cmd, User &usr, SocketServer &server);

void					cap(User &user, SocketServer &server, std::vector<std::string> &params);
void					pass(User &user, SocketServer &server, std::vector<std::string> &params);
void					nick(User &user, SocketServer &server, std::vector<std::string> &params);
void					user(User &user, SocketServer &server, std::vector<std::string> &params);
void                    whois(User &user, SocketServer &server, std::vector<std::string> &params);
void                    ping(User &user, SocketServer &server, std::vector<std::string> &params);
void                    pong(User &user, SocketServer &server, std::vector<std::string> &params);
void                    quit(User &user, SocketServer &server, std::vector<std::string> &params);

std::vector<std::string>    splitSetter(std::string param);

void                    join(User &user, SocketServer &server, std::vector<std::string> &params);
void                    invite(User &user, SocketServer &server, std::vector<std::string> &params);
void                    kick(User &user, SocketServer &server, std::vector<std::string> &params);
void                    topic(User &user, SocketServer &server, std::vector<std::string> &params);
void                    part(User &user, SocketServer &server, std::vector<std::string> &params);
void                    mode(User &user, SocketServer &server, std::vector<std::string> &params);



#endif