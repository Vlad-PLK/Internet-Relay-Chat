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
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <unistd.h>

class SocketServer
{
private:
	int							sockfd;
	int							sock_opt;
	int							port;
	std::string					password;
	struct sockaddr_in 			addr;
public:
	SocketServer(int _port, std::string _password);
	~SocketServer();

	int					getSockfd(void) const;
	int					getPort(void) const;
	const std::string 	&getPassword(void) const;
	void				createSocket(void);
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