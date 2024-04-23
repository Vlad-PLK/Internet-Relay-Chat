/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_server.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:58:44 by vpolojie          #+#    #+#             */
/*   Updated: 2024/04/23 17:11:58 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include "socket.hpp"
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <unistd.h>

int     parse_buffer(std::string buf, t_user &user)
{
    std::string tmp;
    for (size_t i=0; i != buf.size(); i++)
    {
        if (buf[i] != '\r')
            tmp.append(&buf[i]);
    }
}

void    ft_init_socket(int port)
{
    t_init_sock        init_sock;
    struct sockaddr_in acc_addr;
    socklen_t          acc_length = 0;
    std::vector<struct pollfd> tab_fd;
    std::vector<t_user> user_tab;
    t_user              tmp_user;
    std::vector<struct pollfd>::iterator it;
    struct pollfd       fd_in;
    struct pollfd       fd_tmp;
    char                buffer[512];
    std::string str;

    //AF_INET = IPv4 Internet Protocol
    //SOCK_STREAM = socket providing sequenced, reliable, two way communications
    
    //////////server socket initialisation//////////
    init_sock.sock_opt = 1;
    init_sock.sockfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(init_sock.sockfd, SOL_SOCKET, SO_REUSEADDR, &init_sock.sock_opt, sizeof(int));
    if (init_sock.sockfd == -1)
        perror("socket not created !");
    init_sock.addr.sin_family = AF_INET;
    init_sock.addr.sin_addr.s_addr = INADDR_ANY;
    init_sock.addr.sin_port = htons(port);
    fd_in.fd = init_sock.sockfd;
    fd_in.events = POLLIN;
    bind(init_sock.sockfd, (struct sockaddr *)&init_sock.addr, sizeof(init_sock.addr));
    listen(init_sock.sockfd, 10);
    //////////server socket initialisation//////////

    //////////main loop//////////
    while (1)
    {
        tab_fd.push_back(fd_in);
        tab_fd[0].fd = init_sock.sockfd;
        poll(tab_fd.data(), tab_fd.size(), 5000);
        if (tab_fd[0].revents == POLLIN)
        {
            fd_tmp.fd = accept(tab_fd[0].fd, (struct sockaddr *)&acc_addr, &acc_length);
            fd_tmp.events = POLLIN;
            tab_fd.push_back(fd_tmp);
            std::cout << "New Client" << std::endl;
            // users.push_back(User(socket))
        }
        for (it = tab_fd.begin()++; it != tab_fd.end(); it++)
        {
            if (it->revents == POLLIN)
            {
                /*
                user.recv()
                if (user.has_buffer_command()) {
                    std::vector<string> cmd = user.get_command();
                    handle_commad(user, cmd)
                }
                */
                if (read(it->fd, &buffer, 512) != -1)
                {
                    /*
                    
                    */
                    str.append(buffer);
                    if (parse_buffer(str, tmp_user) == 0)
                        user_tab.push_back(tmp_user);
                    send(it->fd, "001 vladplk :Welcome to my Network vladplk\r\n", 56, MSG_CONFIRM);
                }
                else
                    std::cout << "";
            }
        }
    }
    //////////main loop//////////

    //acc_length = sizeof(acc_addr);
    //acc_sockfd = accept(sockfd, (struct sockaddr *)&acc_addr, &acc_length);
    //printf("New client #%d from %s:%d\n", sockfd,
	 //inet_ntoa(acc_addr.sin_addr), ntohs(acc_addr.sin_port));
    ///accept(sockfd, (struct sockaddr *)&addr, addr);
    //  sockfd = socket(int socket_family, int socket_type, int protocol); //
        //  socket -> creates a socket
        //  bind -> create the range of addresses to listen from
        //  connect -> connects a socket  to  a  remote socket  address
        //  listen -> tells the socket that new connections shall be accepted
        //  accept -> is used to get a new socket with a new incoming connection
        //  poll and select wait for arriving data or readiness to send data
            // + the standard input output operations like write, send, read can be used to read and 
            // write data
    /*
        When a socket is created with socket(2), it exists in a name space (ad‐
       dress family) but has no address assigned to it.   bind()  assigns  the
       address  specified  by  addr  to the socket referred to by the file de‐
       scriptor sockfd.  addrlen specifies the size, in bytes, of the  address
       structure  pointed to by addr.  Traditionally, this operation is called
       “assigning a name to a socket”.

    */
    return ;
}