/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:59:54 by vpolojie          #+#    #+#             */
/*   Updated: 2024/04/24 10:55:09 by vpolojie         ###   ########.fr       */
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
#include <sys/select.h> // for select()
#include <signal.h>     // for signal()
#include <stdexcept>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include "User.hpp"
#include "Channel.hpp"

class User;

class SocketServer
{
private:
	int							sockfd;
	int							sock_opt;
	int							port;
	std::string					password;
	struct sockaddr_in 			addr;
	std::time_t					date;
	mutable std::vector<User> 	allUsers;
 	// std::vector<Channel> allChannels;

public:
	SocketServer(int _port, std::string _password);
	~SocketServer();

	int					getSockfd(void) const;
	int					getPort(void) const;
	const std::string 	&getPassword(void) const;
	void				createSocket(void);

	User					*getUser(std::string name); //const?
	User 					*getUser(int fd); //const?
	void 					addUser(const User& user) const;
	const std::vector<User>	&getAllUsers() const;
};

class Message  {
private:
	std::string buffer;
public:
	int is_command_buffer(); // si \r\n dans buffer
};

void    ft_init_server_socket(int port, std::string password);
void    main_loop(const SocketServer &main_socket);

#endif