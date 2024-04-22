/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_server.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:58:44 by vpolojie          #+#    #+#             */
/*   Updated: 2024/04/22 15:42:54 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "socket.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>

void    ft_create_socket(int port)
{
    int sockfd;
    int acc_sockfd;
    struct sockaddr_in addr;
    struct sockaddr_in acc_addr;
    socklen_t          acc_length;

    //AF_INET = IPv4 Internet Protocol
    //SOCK_STREAM = socket providing sequenced, reliable, two way communications
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        perror("socket not created !");
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    listen(sockfd, 10);
    acc_length = sizeof(acc_addr);
    acc_sockfd = accept(sockfd, (struct sockaddr *)&acc_addr, &acc_length);
    printf("New client #%d from %s:%d\n", sockfd,
	 inet_ntoa(acc_addr.sin_addr), ntohs(acc_addr.sin_port));
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