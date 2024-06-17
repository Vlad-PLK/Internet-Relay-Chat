/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:50:20 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/17 09:08:47 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include "SocketServer.hpp"
#include "Command.hpp"
#include <exception>

User::User() : userfd(0), admin_state(0), current_state(0)
{
}

User::User(int fd, int _admin_state, int _current_state) : userfd(fd), admin_state(_admin_state), current_state(_current_state)
{
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
	this->nickname = nname;
}

void	User::setUsername(const std::string &uname)
{
	this->username = uname;
}

void	User::setRealname(const std::string &uname)
{
	this->realname = uname;
}

void	User::setIp(const std::string &uname)
{
	this->ip = uname;
}


void	User::setCurrentState(int state)
{
	if (state == ACCEPTED)
		this->current_state = ACCEPTED;
	else if (state == WAITING_FOR_APPROVAL)
		this->current_state = WAITING_FOR_APPROVAL;
	else if (state == QUIT)
		this->current_state = QUIT;
	else if (state == ALREADY_REGISTRED)
		this->current_state = ALREADY_REGISTRED;
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

void 	User::setBuffer(char *str)
{
	this->buffer += str;
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

void User::parsing_and_handle(SocketServer &server)
{
    std::string tmp;
	char 		buf[513];
    Command 	tmpcmd;
    size_t 		pos = 0;
	ssize_t		read_value = 0;

	memset(buf, 0, sizeof(buf));
	read_value = recv(this->userfd, buf, 512, MSG_DONTWAIT | MSG_NOSIGNAL);
	if (read_value > 0)
		buf[read_value] = 0;
	else 
		throw DisconnectException();
	this->buffer += buf;
	//std::cout << "buffer : " << this->buffer << " buf : " << buf << std::endl;
    for (size_t i = 0; i < buffer.size(); i++)
    {
        if (i + 1 < this->buffer.size() && this->buffer[i] == '\r' && this->buffer[i + 1] == '\n')
        {
            tmp = this->buffer.substr(pos, i - pos);
            tmpcmd.setRawCommand(tmp);
            tmpcmd.setCmdParams();
            HandleCommand(tmpcmd, *this, server);
            pos = i + 2;
            tmp.clear();
            tmpcmd.clearCmd();
        }
    }
    this->buffer.erase(0, pos);
	//std::cout << "buffer after flush : " << this->buffer << " buffer size : " << this->buffer.size() << " user fd : " << this->getFD() << std::endl;
}

std::ostream &operator<<(std::ostream &output, const User &user)
{
	output << "nickname : " << user.getNickname() << " username : " << user.getUsername() << " fd : " << user.getFD() << " current status : " << user.getCurrentState() << std::endl;
	return (output);
}
