/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:45:37 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/30 14:19:53 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "SocketServer.hpp"
#include "Server_comments.hpp"

static const Command_Dictionnary cmds[] =
{
    {"CAP LS", cap},
    {"PASS", pass},
    {"NICK", nick},
    {"USER", user},
	// {"MODE", Mode},
	{"WHOIS", whois},
	{"PING", ping},
    {"JOIN", join},
    {"INVITE", invite},
    {"PART", part},
    {"TOPIC", topic},
    {"KICK", kick},

};

void HandleCommand(Command &cmd, User &usr, Channel &chl, SocketServer &server)
{
	(void)chl;
    for (long unsigned int i = 0; i < sizeof(cmds) / sizeof(cmds[0]); i++)
    {
        if (cmd.getCmdName() == cmds[i].name)
            cmds[i].fct(usr, chl, server, cmd.getParams());
        // handle unknown commands ? //
    }
}

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