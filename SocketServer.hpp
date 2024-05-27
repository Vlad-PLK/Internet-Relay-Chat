/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:59:54 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/27 10:17:09 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETSERVER_HPP
#define SOCKETSERVER_HPP
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <string>
#include <vector>
#include <map>
#include <sys/select.h> // for select()
#include <signal.h>     // for signal()
#include <stdexcept>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <ctime>
#include <sstream>
#include <unistd.h>
#include "User.hpp"
#include "Channel.hpp"
#include "Server_comments.hpp"
#include "Command.hpp"

class User;

class Channel;

class SocketServer
{
private:
	int							sockfd;
	int							sock_opt;
	int							port;
	std::string					password;
	struct sockaddr_in 			addr;
	std::time_t					date;
	mutable std::vector<User> 	_allUsers;
 	std::vector<Channel> 		_allChannels;

public:
	SocketServer(int _port, std::string _password);
	~SocketServer();

	int					getSockfd(void) const;
	int					getPort(void) const;
	const std::string 	&getPassword(void) const;
	void				createSocket(void);

	User					*getUser(std::string name); //const?
	void 					addUser(const User& user) const;
	const std::vector<User>	&getAllUsers() const;
	Channel					*getChannel(std::string title);
	void					addChannel(std::string title);
	void					addChannel(std::string title, std::string password);

	bool					findChannel(std::string channel_name);

	void					join(User &user, Channel &channel, std::vector<std::string> params);
	///void					pass(User &user, Channel &channel, std::vector<std::string> params);
	///void					nick(User &user, Channel &channel, std::vector<std::string> params);
	///void					user(User &user, Channel &channel, std::vector<std::string> params);
};

class Message  {
private:
	std::string buffer;
public:
	int is_command_buffer(); // si \r\n dans buffer
};

void    ft_init_server_socket(int port, std::string password);
void    main_loop(SocketServer &main_socket);

#endif