/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:50:20 by vpolojie          #+#    #+#             */
/*   Updated: 2024/04/25 09:24:45 by vpolojie         ###   ########.fr       */
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

void User::parse_cmd(std::string &buf)
{
	std::string tmp;
	size_t		pos = 0;
	for (size_t i=0; i != buf.size(); i++)
	{
		if (buf[i] == '\r')
		{
			tmp = buf.substr(pos, i - pos);
			pos = i;
			cmds.push_back(tmp);
			tmp.clear();
		}
	}
	std::cout << cmds[0] << std::endl;
}

int	User::process_cmd(std::string buf)
{
	///connection entrante///
	///parser le buf en tableau de strings///
	///etudier chaque commandes///
	///stocker d'eventuelles variables///
	///creer la reponse, clean le tableau de commandes et le buffer///
	parse_cmd(buf);
	for (size_t i=0; i != cmds.size(); i++)
		std::cout << cmds[i];
	//std::cout << cmds[0];
	//if (cmds[0].compare(0, 7, "CAP LS") == 0)
	//{
	//	std::cout << cmds[0];
	//}
	return (ACCEPTED);
}

