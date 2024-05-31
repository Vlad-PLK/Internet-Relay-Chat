/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:50:20 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/29 12:38:28 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "SocketServer.hpp"
#include "Command.hpp"

User::User() : userfd(0), admin_state(0), current_state(0)
{
}

User::User(int fd, int _admin_state, int _current_state) : userfd(fd), admin_state(_admin_state), current_state(_current_state)
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

void	User::deleteChannelRights(std::string title)
{
	for (std::map<std::string, std::string>::iterator it = this->_channelRights.begin(); it != this->_channelRights.end(); ++it)
	{
		if (it->first == title)
		{
			this->_channelRights.erase(it);
			break;
		}
	}
}

void	User::usr_send(const std::string &response)
{
    send(this->userfd, response.c_str(), response.size(), MSG_DONTWAIT | MSG_NOSIGNAL);
    std::cout << "--> Message sent to client " << this->userfd - 3 << " = " << response << std::endl;
}

void User::usr_clean(void)
{
	this->nickname.clear();
	this->username.clear();
}

void User::parsing_and_handle(std::string &buf, SocketServer &server)
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

int	User::process_cmd(std::string buf, SocketServer &server)
{
	parsing_and_handle(buf, server);
	return (ACCEPTED);
}

std::ostream &operator<<(std::ostream &output, const User &user)
{
	output << "nickname : " << user.getNickname() << " username : " << user.getUsername() << " fd : " << user.getFD() << " current status : " << user.getCurrentState() << std::endl;
	return (output);
}

// void User::cmds_center(std::vector<std::string> cmd)
// {
// 	for (size_t i = 0; i < cmd.back().length(); i++)
// 	{
// 		std::cout << "cmd.back()[" << i << "] :" << cmd.back()[i] << std::endl;
// 		if (cmd.back()[i] == ' ')
// 			break;
// 		else
// 			cmd.back()[i] = std::toupper(cmd.back()[i]);
// 	}
	// std::cout << "cmd is: ";
    // for (size_t i = 0; i < cmd.size(); ++i)
	// {
    //     std::cout << "(" << i << ") " << cmd[i];
    //     if (i != cmd.size() - 1) {
    //         std::cout << ", ";
    //     }
    // }
    // std::cout << std::endl;

	
	// std::string allcmdnames[2] = {"JOIN", "PART"};	
	// cmdPtr allcmds[2] = { &SocketServer::join, &SocketServer::part};
	// for (int index = 0; index < 1; index++)
	// {
	// 	if (cmd.back() == allcmdnames[index])
	// 	{
	// 		(this->*allcmds[index])(cmd);
	// 		return ;
	// 	}
	// }
// }

// void User::parse_buffer(std::string &buf)
// {
// 	std::string tmp;
// 	size_t		pos = 0;

// 	buffer.append(buf);
// 	for (size_t i=0; i != buffer.size(); i++)
// 	{
// 		if (buffer[i] == '\r' && buffer[i + 1] == '\n')
// 		{
// 			Command cmd;
// 			tmp = buffer.substr(pos, i - pos);
// 			cmd.setRawCommand(tmp);
// 			pos = i + 2;
// 			this->cmds.push_back(cmd);
// 			tmp.clear();
// 		}
// 	}
// 	buffer.erase(0, pos);
// }


// void User::parse_cmds()
// {
// 	std::vector<Command>::iterator it;
// 	for (it = this->cmds.begin(); it != this->cmds.end(); it++)
// 	{
// 		it->setCmdParams();
// 		std::cout << "CMD NAME : " << it->getCmd() << " CMD FIRST PARAM : " << it->getParams().front() << std::endl;
// 		//std::cout << "CMD NAME : " << it->getCmd() << "FIRST PARAM NAME : " << it->getParams().front() << std::endl;
// 		// first COMMAND
// 		// then Params
// 		// end Trailing
// 	}
// }

// void User::setPassword(const std::string &pass)
// {
// 	this->server_password.assign(pass);
// }

// void User::setAnswer(void)
// {
// 	this->answer.append("001 ").append(this->getNickname()).append(" :Welcome to my Network ").append(this->getNickname()).append("\r\n");
// 	std::cout << this->getAnswer() << std::endl;
// }

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

// int	User::process_cmd(std::string buf)
// {
// 	parse_buffer(buf);
// 	parse_cmds();
// 	return (ACCEPTED);
// 		if (find_cmd() == true)
// 		{
// 			handle_cmd();
// 			return (ACCEPTED);
// 		}
// 		else
// 			return (REJECTED);
	//if (connexion_try() == ACCEPTED)
	//	return (ACCEPTED);
	//else 
	//	return (REJECTED);
// }
