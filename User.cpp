/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:50:20 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/27 10:23:40 by vpolojie         ###   ########.fr       */
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

std::vector<Command> &User::getCmds(void)
{
	return (this->cmds);
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

void User::parse_buffer(std::string &buf)
{
	std::string tmp;
	Command		*cmd;
	size_t		pos = 0;

	buffer.append(buf);
	for (size_t i=0; i != buffer.size(); i++)
	{
		if (buffer[i] == '\r' && buffer[i + 1] == '\n')
		{
			cmd = new Command;
			tmp = buffer.substr(pos, i - pos);
			cmd->setRawCommand(tmp);
			pos = i + 2;
			this->cmds.push_back(*cmd);
			tmp.clear();
			delete cmd;
		}
	}
	buffer.erase(0, pos);
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
        if (cmd.getCmd() == cmds[i].name)
		{
			//std::cout << "CMD INDEX IN DICT " << i << " CMD NAME : " << cmd.getCmd() << " FIRST PARAM NAME : " << cmd.getParams().front() << std::endl;
            cmds[i].fct(usr, chl, server, cmd.getParams());
		}
    }
}

void User::parse_cmds(SocketServer &server)
{
	std::vector<Command>::iterator it;
	Channel							chnl;
	for (it = this->cmds.begin(); it != this->cmds.end(); it++)
	{
		it->setCmdParams();
		//std::cout << "CMD NAME : " << it->getCmd() << " FIRST PARAM NAME : " << it->getParams().front() << std::endl;
		HandleCommand(*it, *this, chnl, server);
		// first COMMAND
		// then Params
		// end Trailing
	}
}

void User::setPassword(const std::string &pass)
{
	this->server_password.assign(pass);
}

void User::setAnswer(std::string ans)
{
	this->answer = ans;
}

// int User::connexion_try(void)
// {
// 	std::vector<std::string>::iterator it;
// 	for (it = this->cmds.begin(); it != this->cmds.end(); it++)
// 	{
// 		if (it->compare(0, 4, "PASS") == 0 && it->compare(6, server_password.size(), server_password) == 0)
// 			setCurrentState(ACCEPTED);
// 		else if (current_state == ACCEPTED && it->compare(0, 4, "NICK") == 0)
// 			setNickname(it->substr(5, std::string::npos));
// 		else if (current_state == ACCEPTED && it->compare(0, 4, "USER") == 0)
// 			setUsername(it->substr(5, it->find(" ", 6) - 5));
// 		it->clear();
// 	}
// 	if (this->getNickname().size() == 0 || this->getUsername().size() == 0)
// 		return (REJECTED);
// 	this->answer.append("001 ").append(this->getNickname()).append(" :Welcome to my Network ").append(this->getNickname()).append("\r\n");
// 	return (ACCEPTED); 
// }

int	User::process_cmd(std::string buf, SocketServer &server)
{
	parse_buffer(buf);
	parse_cmds(server);
	return (ACCEPTED);
	/*if (find_cmd() == true)
		return (ACCEPTED);
	else
		return (REJECTED);
	*/
	//if (connexion_try() == ACCEPTED)
	//	return (ACCEPTED);
	//else 
	//	return (REJECTED);
}


std::ostream &operator<<(std::ostream &output, const User &user)
{
	output << "nickname : " << user.getNickname() << " username : " << user.getUsername() << " fd : " << user.getFD() << " current status : " << user.getCurrentState() << std::endl;
	return (output);
}
