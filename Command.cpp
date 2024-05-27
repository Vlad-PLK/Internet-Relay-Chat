/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:45:37 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/27 10:25:40 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "SocketServer.hpp"

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

std::string const &Command::getCmd(void)
{
    return (this->cmd_name);
}

std::vector<std::string> &Command::getParams(void)
{
    return (this->params);
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
    if (server.getPassword() == params.front() && user.getCurrentState() == WAITING_FOR_APPROVAL)
        user.setCurrentState(ACCEPTED);
}

void					nick(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)server;
    if (user.getCurrentState() == ACCEPTED)
        user.setNickname(params.front());
}
void					user(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)server;
    if (user.getCurrentState() == ACCEPTED)
        user.setUsername(params.front());
    user.setAnswer("001 " + user.getNickname() + " :Welcome to my Network " + user.getNickname() + "\r\n");
}