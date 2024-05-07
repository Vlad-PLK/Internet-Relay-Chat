/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:50:20 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/07 15:28:00 by vpolojie         ###   ########.fr       */
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

void User::parse_cmd(std::string &buf)
{
	std::string tmp;
	size_t		pos = 0;
	for (size_t i=0; i != buf.size(); i++)
	{
		if (buf[i] == '\r' && buf[i + 1] == '\n')
		{
			tmp = buf.substr(pos, i - pos);
			pos = i + 2;
			this->cmds.push_back(tmp);
			tmp.clear();
		}
	}
}

void User::setPassword(const std::string &pass)
{
	this->server_password.assign(pass);
}

void User::setAnswer(void)
{
	this->answer.append("001 ").append(this->getNickname()).append(" :Welcome to my Network ").append(this->getNickname()).append("\r\n");
	std::cout << this->getAnswer() << std::endl;
}

int User::connexion_try(void)
{
	std::vector<std::string>::iterator it;
	for (it = this->cmds.begin(); it != this->cmds.end(); it++)
	{
		if (it->compare(0, 4, "PASS") == 0 && it->compare(6, server_password.size(), server_password) == 0)
			setCurrentState(ACCEPTED);
		else if (current_state == ACCEPTED && it->compare(0, 4, "NICK") == 0)
			setNickname(it->substr(5, std::string::npos));
		else if (current_state == ACCEPTED && it->compare(0, 4, "USER") == 0)
			setUsername(it->substr(5, it->find(" ", 6) - 5));
		it->clear();
	}
	if (this->getNickname().size() == 0 || this->getUsername().size() == 0)
		return (REJECTED);
	this->answer.append("001 ").append(this->getNickname()).append(" :Welcome to my Network ").append(this->getNickname()).append("\r\n");
	//std::cout << answer << std::endl;
	return (ACCEPTED); 
}

int	User::process_cmd(std::string buf)
{
	parse_cmd(buf);
	if (connexion_try() == ACCEPTED)
		return (ACCEPTED);
	else 
		return (REJECTED);
}

std::ostream &operator<<(std::ostream &output, const User &user)
{
	output << "nickname : " << user.getNickname() << " username : " << user.getUsername() << " fd : " << user.getFD() << " current status : " << user.getCurrentState() << std::endl;
	return (output);
}
