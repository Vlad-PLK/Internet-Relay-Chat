/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:45:37 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/28 10:44:06 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "SocketServer.hpp"
#include "Server_comments.hpp"

Command::Command()
{
}

Command::~Command(){}

void Command::setRawCommand(std::string &cmd)
{
    this->raw_command.assign(cmd);
}

void Command::setCmdName()
{
    return ;
}

void Command::setCmdParams()
{
    size_t  index = 0;

    if (this->raw_command[0] == ':')
       index = this->raw_command.find(' ', 0);
    this->cmd_name = this->raw_command.substr(index, this->raw_command.find(' ', index) - index);
    index = this->raw_command.find(' ', index);
    while (index <= this->raw_command.size())
    {
		if (this->raw_command[index + 1] != ':')
        {
            index++;
            this->params.push_back(this->raw_command.substr(index, this->raw_command.find(' ', index) - index));
            index = this->raw_command.find(' ', index);
        }
        else
        {
            index++;
            this->params.push_back(this->raw_command.substr(index + 2, std::string::npos));
            break ;
        }
	}
}

std::string const &Command::getRawCommand(void)
{
    return (this->raw_command);
}

std::string const &Command::getCmdName(void)
{
    return (this->cmd_name);
}

std::vector<std::string> &Command::getParams(void)
{
    return (this->params);
}

void    Command::clearCmd(void)
{
    this->raw_command.clear();
    this->cmd_name.clear();
    this->params.clear();
}

void					cap(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)params;
    (void)server;
    user.setCurrentState(WAITING_FOR_APPROVAL);
}

void					pass(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    if (server.getPassword() == params.front())
        user.setCurrentState(ACCEPTED);
    else
        user.setCurrentState(REJECTED);
}

void					nick(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)server;
    std::string answer;
    user.setNickname(params.front());
    if (user.getCurrentState() == REJECTED)
    {
        answer = ERR_PASSWDMISMATCH(user.getNickname());
        send(user.getFD(), answer.c_str(), answer.size(), MSG_DONTWAIT | MSG_NOSIGNAL);
        //send(user.getFD(), "ERROR: incorrect password\r\n", 28, MSG_DONTWAIT | MSG_NOSIGNAL);
    }
}
void					user(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)server;
    if (user.getCurrentState() == ACCEPTED)
    {
        user.setUsername(params.front());
        user.setAnswer("001 " + user.getNickname() + " :Welcome to 42's Network " + user.getNickname() + "\r\n");
        send(user.getFD(), user.getAnswer().c_str(), user.getAnswerSize(), MSG_DONTWAIT | MSG_NOSIGNAL);
        user.setAnswer("002 " + user.getNickname() + " :Your host is VPTV, running version lol.dev.c3plus\r\n");
        send(user.getFD(), user.getAnswer().c_str(), user.getAnswerSize(), MSG_DONTWAIT | MSG_NOSIGNAL);
        user.setAnswer("003 " + user.getNickname() + " :This server was created 2024-05-28 10:11 CEST:+0200\r\n");
        send(user.getFD(), user.getAnswer().c_str(), user.getAnswerSize(), MSG_DONTWAIT | MSG_NOSIGNAL);
    }
}

void					whois(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)server;
    (void)params;
    std::string answer;
    answer = "318 " + user.getUsername() + " " + user.getNickname() + " :END of /WHOIS list\r\n";
    send(user.getFD(), answer.c_str(), answer.size(), MSG_DONTWAIT | MSG_NOSIGNAL);
}

void					mode(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)server;
    (void)params;
    std::string answer;
    answer = "221 " + user.getNickname() + " +i\r\n";
    send(user.getFD(), answer.c_str(), answer.size(), MSG_DONTWAIT | MSG_NOSIGNAL);
}

void					ping(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)server;
    (void)params;
    std::string answer;
    answer = "PONG " + params.front() + "\r\n";
    send(user.getFD(), answer.c_str(), answer.size(), MSG_DONTWAIT | MSG_NOSIGNAL);
}