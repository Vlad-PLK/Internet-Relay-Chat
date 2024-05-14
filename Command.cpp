/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:45:37 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/14 15:04:51 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

Command::Command(){}

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
    size_t      index = 0;

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

