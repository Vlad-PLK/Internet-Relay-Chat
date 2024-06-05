/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:59:54 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/05 10:01:16 by vpolojie         ###   ########.fr       */
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
#include <sys/select.h>
#include <signal.h>
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
	std::vector<User *> 		_allUsers;
 	std::vector<Channel *> 		_allChannels;

public:
	SocketServer(int _port, std::string _password);
	~SocketServer();

	void				printAllChannels();
	int					getSockfd(void) const;
	int					getPort(void) const;
	const std::string 	&getPassword(void) const;
	void				createSocket(void);

	User					*getUser(std::string name); //const?
	void 					addUser(User& user);
	std::vector<User *>	&getAllUsers();
	Channel					*getChannel(std::string title);
	void					addChannel(std::string title);
	void					addChannel(std::string title, std::string password);
	void					deleteChannel(std::string title);

	bool					findChannel(std::string channel_title);
	bool					findUser(std::string user_nickname);

	int						is_in_range(int port);
	typedef void        (SocketServer::*cmdPtr)(std::vector<std::string> cmd);
    void                cmds_center(std::vector<std::string> cmd);
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