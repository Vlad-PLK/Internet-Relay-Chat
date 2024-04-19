/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_server.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:58:44 by vpolojie          #+#    #+#             */
/*   Updated: 2024/04/19 17:09:12 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <sys/socket.h>

void    ft_create_socket(int port)
{
    int sockfd;

    //  sockfd = socket(int socket_family, int socket_type, int protocol); //
        //  socket -> creates a socket
        //  connect -> connects a socket  to  a  remote socket  address
        //  listen -> tells the socket that new connections shall be accepted
        //  accept -> is used to get a new socket with a new incoming connection
        //  poll and select wait for arriving data or readiness to send data
            // + the standard input output operations like write, send, read can be used to read and 
            // write data
    return ;
}