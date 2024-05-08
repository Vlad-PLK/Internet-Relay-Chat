/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:50:20 by vpolojie          #+#    #+#             */
/*   Updated: 2024/04/26 08:51:46 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "SocketServer.hpp"

User::User() : userfd(0), admin_state(0), current_state(0)
{
}

User::User(int fd, int logstate) : userfd(fd), current_state(logstate)
{
	std::cout << "New User trying to join server" << std::endl;
}

User::~User()
{

}

const std::string   &User::getNickname(void) const
{
	return (this->nickname);
}

const std::string   &User::getUsername(void) const
{
	return (this->username);
}

const std::string	User::getAnswer(void)
{
	return (this->answer);
}

int	User::getFD(void) const
{
	return (this->userfd);
}

void	User::setNickname(const std::string &nname)
{
	this->nickname.assign(nname);
}

void	User::setUsername(const std::string &uname)
{
	this->username.assign(uname);
}

void	User::setCurrentState(int state)
{
	if (state == ACCEPTED)
		this->current_state = ACCEPTED;
	else if (state == WAITING_FOR_APPROVAL)
		this->current_state = WAITING_FOR_APPROVAL;
	else
		this->current_state = REJECTED;
}

void	User::setAdminState(int state)
{
	if (state == IS_ADMIN)
		this->admin_state = IS_ADMIN;
	else
		this->admin_state = NOT_ADMIN;
}

void	User::setFD(int fd)
{
	this->userfd = fd;
}

void User::sendAndPrint(std::string response, int length, int flag)
{
    send(this->userfd, response.c_str(), length, flag);
    std::cout << "--> Message sent to client " << this->userfd << " = " << response << std::endl;
}


void User::cmds_center(std::vector<std::string> cmd)
{
	for (size_t i = 0; i < cmd.back().length(); i++)
	{
		std::cout << "cmd.back()[" << i << "] :" << cmd.back()[i] << std::endl;
		if (cmd.back()[i] == ' ')
			break;
		else
			cmd.back()[i] = std::toupper(cmd.back()[i]);
	}
	std::cout << "cmd is: ";
    for (size_t i = 0; i < cmd.size(); ++i)
	{
        std::cout << "(" << i << ") " << cmd[i];
        if (i != cmd.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
	// if (cmd[2] != "\0" && cmd[2] == "hello")
	// 	this->hello(cmd);
	std::string allcmdnames[2] = {"QUIT", "HELLO"};	
	cmdPtr allcmds[2] = { &User::quit, &User::hello};
	for (int index = 0; index < 2; index++)
	{
		if (cmd.back() == allcmdnames[index])
		{
			(this->*allcmds[index])(cmd);
			return ;
		}
	}
}

void User::parse_cmd(std::string &buf)
{
	std::cout << "HERE cmd parse" << std::endl;
	std::string tmp;
	size_t		pos = 0;
	for (size_t i = 0; i != buf.size(); i++)
	{
		if (buf[i] == '\r' && buf[i + 1] == '\n')
		{
			tmp = buf.substr(pos, i - pos);
			pos = i + 2;
			cmds.push_back(tmp);
			this->cmds_center(cmds);
			// std::cout << tmp << std::endl;
			tmp.clear();
		}
	}
}

void User::setPassword(const std::string &pass)
{
	this->server_password.assign(pass);
}

int User::connexion_try(void)
{
	std::vector<std::string>::iterator it;
	for (it = cmds.begin(); it != cmds.end(); it++)
	{
		//std::cout << it->data() << std::endl;
		if (it->compare(0, 7, "CAP LS") == 0)
		{
			std::cout << "CAP LS" << std::endl;
			//cmds.erase(it);
		}
		else if (it->compare(0, 2, "PA") == 0)
		{
			//setCurrentState(ACCEPTED);
			std::cout << it->substr(0, 5) << std::endl;
		}
		else if (current_state == ACCEPTED && it->compare(0, 5, "NICK") == 0)
			setNickname(it->substr(6, std::string::npos));
		else if (current_state == ACCEPTED && it->compare(0, 5, "USER") == 0)
			setUsername(it->substr(6, it->find(" ", 6)));
	}
	std::cout << getNickname() << " " << getUsername() << std::endl;
	return (ACCEPTED); 
}

int	User::process_cmd(std::string buf)
{
	std::cout << "buffer_cmd :" << buf << std::endl;
	parse_cmd(buf);
	return (ACCEPTED);
	// if (connexion_try() == ACCEPTED)
	// 	return (ACCEPTED);
	// else 
	// 	return (REJECTED);
}

