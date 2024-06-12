/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:50:20 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/12 11:01:01 by vpolojie         ###   ########.fr       */
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

const std::string   &User::getRealname(void) const
{
	return (this->realname);
}

const std::string   &User::getIp(void) const
{
	return (this->ip);
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

void	User::setRealname(const std::string &uname)
{
	this->realname.assign(uname);
}

void	User::setIp(const std::string &uname)
{
	this->ip.assign(uname);
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

void User::usr_send(const std::string &reply)
{
    send(this->userfd, reply.c_str(), reply.size(), MSG_DONTWAIT | MSG_NOSIGNAL);
}

void User::usr_clean(void)
{
	this->nickname.clear();
	this->username.clear();
	close(this->userfd);
}

void User::parsing_and_handle(std::string &buf, SocketServer &server)
{
    std::string tmp;
    Command tmpcmd;
    size_t pos = 0;

    buffer.append(buf);
    for (size_t i = 0; i < buffer.size(); i++)
    {
        if (i + 1 < buffer.size() && buffer[i] == '\r' && buffer[i + 1] == '\n')
        {
            tmp = buffer.substr(pos, i - pos);
            tmpcmd.setRawCommand(tmp);
            tmpcmd.setCmdParams();
            HandleCommand(tmpcmd, *this, server);
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
