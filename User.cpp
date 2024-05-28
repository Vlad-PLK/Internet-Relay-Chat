/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:50:20 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/28 09:06:22 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "SocketServer.hpp"
#include "Command.hpp"

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

const std::string   &User::getPasssword(void) const
{
	return (this->server_password);
}

std::string	&User::getAnswer(void)
{
	return (this->answer);
}

int			 User::getAnswerSize(void) const
{
	return (this->answer.size());
}

int	User::getFD(void) const
{
	return (this->userfd);
}

int User::getCurrentState(void) const
{
	return (this->current_state);
}

std::map<std::string, std::string>  User::getChannelRights(void) const
{
	return (this->_channelRights);
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

bool	User::parseRights(std::string userRights, std::string channelRights)
{
	int count = 0;
	int i = -1;
	while (++i < (int)channelRights.length())
	{
		int j = -1;
		while (userRights[++j])
		{
			if (userRights[j] == channelRights[i])
			{
				count++;
				break;
			}
		}
	}
	if (count == (int)channelRights.length())
		return true;
	return false;
}

bool	User::checkRights(const std::string channelTitle, const std::string channelRights)
{
	for (std::map<std::string, std::string>::iterator it = this->_channelRights.begin(); it != this->_channelRights.end(); ++it)
	{
		if (it->first == channelTitle)
			return (parseRights(it->second, channelRights));
	}
	return false; //ERROR MSG ?(what to do if title not found?)
}

void User::my_send(std::string response, int length, int flag)
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
	// std::cout << "cmd is: ";
    // for (size_t i = 0; i < cmd.size(); ++i)
	// {
    //     std::cout << "(" << i << ") " << cmd[i];
    //     if (i != cmd.size() - 1) {
    //         std::cout << ", ";
    //     }
    // }
    // std::cout << std::endl;
	std::string allcmdnames[2] = {"QUIT"};	
	cmdPtr allcmds[2] = { &User::quit};
	for (int index = 0; index < 1; index++)
	{
		if (cmd.back() == allcmdnames[index])
		{
			(this->*allcmds[index])(cmd);
			return ;
		}
	}
}

typedef struct S_Command_Dictionnary{
    std::string name;
    void (*fct)(User &, Channel &, SocketServer &, std::vector<std::string> &);
}Command_Dictionnary;

static const Command_Dictionnary cmds[] = {
    {"CAP LS", cap},
    {"PASS", pass},
    {"NICK", nick},
    {"USER", user},
};

void HandleCommand(Command &cmd, User &usr, Channel &chl, SocketServer &server)
{
	(void)chl;
    for (long unsigned int i = 0; i < sizeof(cmds) / sizeof(cmds[0]); i++)
    {
        if (cmd.getCmdName() == cmds[i].name)
            cmds[i].fct(usr, chl, server, cmd.getParams());
    }
}

void User::parse_buffer(std::string &buf, SocketServer &server)
{
	std::string tmp;
	Command		tmpcmd;
	Channel		channel;
	size_t		pos = 0;

	buffer.append(buf);
	for (size_t i=0; i != buffer.size(); i++)
	{
		if (buffer[i] == '\r' && buffer[i + 1] == '\n')
		{
			tmp = buffer.substr(pos, i - pos);
			tmpcmd.setRawCommand(tmp);
			tmpcmd.setCmdParams();
			HandleCommand(tmpcmd, *this, channel, server);
			pos = i + 2;
			tmp.clear();
			tmpcmd.clearCmd();
		}
	}
	buffer.erase(0, pos);
}

void User::setPassword(const std::string &pass)
{
	this->server_password.assign(pass);
}

void User::setAnswer(std::string ans)
{
	this->answer = ans;
}

int	User::process_cmd(std::string buf, SocketServer &server)
{
	parse_buffer(buf, server);
	return (ACCEPTED);
}


std::ostream &operator<<(std::ostream &output, const User &user)
{
	output << "nickname : " << user.getNickname() << " username : " << user.getUsername() << " fd : " << user.getFD() << " current status : " << user.getCurrentState() << std::endl;
	return (output);
}
