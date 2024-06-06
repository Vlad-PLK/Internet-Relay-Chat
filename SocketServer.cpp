/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:58:44 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/06 10:54:26 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketServer.hpp"

User *SocketServer::getUser(std::string name)
{
    for (std::vector<User *>::iterator it = this->_allUsers.begin(); it != this->_allUsers.end(); ++it)
    {
        if ((*it)->getNickname() == name)
            return (*it); // return pointer to the User
    }
    return NULL;
}

void    SocketServer::printAllChannels()
{
    std::vector<Channel*>::iterator it;
    for (it = this->_allChannels.begin(); it != this->_allChannels.end(); it++)
    {
        std::cout << "CHANNEL NAME : " << (*it)->getTitle()
            << "\nCHANNEL USERS : " << (*it)->getChannelUsers().size() << std::endl;
    }
}

bool    SocketServer::findChannel(std::string title)
{
    std::vector<Channel*>::iterator it;
    for (it = this->_allChannels.begin(); it != this->_allChannels.end(); it++)
    {
        if ((*it)->getTitle() == title)
            return (true);
    }
    return (false);
}

Channel *SocketServer::getChannel(std::string title)
{
    std::vector<Channel*>::iterator it = this->_allChannels.begin();
    while (it != this->_allChannels.end())
    {
        if ((*it)->getTitle() == title)
            break;
        it++;
    }
    return (*it);
}


void    SocketServer::addChannel(std::string title)
{
    Channel *new_channel = new Channel();
    new_channel->setTitle(title);
    new_channel->setTopic("");
    new_channel->setLimit(-1);
    this->_allChannels.push_back(new_channel);
}

void    SocketServer::addChannel(std::string title, std::string password)
{
    Channel new_channel;
    if (title[0] == '#')
        new_channel.setTitle(title);
    else
        new_channel.setTitle('#' + title);
    if (!password.empty()) // Check if the password is not empty
        new_channel.setPassword(password);
    new_channel.setTopic("");
    new_channel.setLimit(-1);
    this->_allChannels.push_back(&new_channel);
}

void	SocketServer::deleteChannel(std::string title)
{
    for (std::vector<Channel *>::iterator it = this->_allChannels.begin(); it != this->_allChannels.end(); ++it)
    {
        if ((*it)->getTitle() == title)
        {
            this->_allChannels.erase(it);
            break;
        }
    }
    // need to free the channel //
}

void    SocketServer::addUser(User *user)
{
    _allUsers.push_back(user);
}

std::vector<User *> &SocketServer::getAllUsers()
{
    return _allUsers;
}

SocketServer::SocketServer(int _port, std::string _password)
{
    sockfd = 0;
    sock_opt = 0;
    port = _port;
    password.assign(_password);
    date = std::time(0);
}

SocketServer::~SocketServer(){

}

void    SocketServer::createSocket(void)
{
    sock_opt = 1;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        perror("Server Socket not created\n");
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &sock_opt, sizeof(int));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    listen(sockfd, 10);
}

int SocketServer::getSockfd(void) const
{
    return (this->sockfd);
}


int SocketServer::getPort(void) const
{
    return (this->port);
}

int SocketServer::is_in_range(int port)
{
    if ((6660 <= port && port <= 6669)
        || (7000 <= port && port <= 7005)
        || port == 6697 
        || port == 8080)
        return (0);
    else 
        return (1);
}

const std::string   &SocketServer::getPassword(void) const
{
    return (this->password);
}

void    ft_init_server_socket(int port, std::string password)
{
    SocketServer        main_socket(port, password);

    if (main_socket.is_in_range(port) != 0)
        throw std::invalid_argument("invalid port number");
    //AF_INET = IPv4 Internet Protocol
    //SOCK_STREAM = socket providing sequenced, reliable, two way communications

    //////////server socket initialisation//////////
    main_socket.createSocket();
    main_loop(main_socket);
    //////////server socket initialisation//////////

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