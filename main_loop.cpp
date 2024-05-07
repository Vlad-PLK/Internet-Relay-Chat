/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:46:58 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/07 11:33:47 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketServer.hpp"
#include "User.hpp"

void    main_loop(const SocketServer &main_socket)
{
    ///////////array of fds part///////////
    std::vector<struct pollfd> tab_fd;
    std::vector<struct pollfd>::iterator it;
    struct pollfd       fd_tmp;
    ///////////array of fds part///////////

    ///////////buffer for read///////////
    char                buffer[513];
    std::string str;
    ///////////buffer for read///////////

    ///////////users///////////
    std::vector<User> users;
    std::vector<User>::iterator user_it;
    User              tmp_user;
    ///////////users///////////

    fd_tmp.fd = main_socket.getSockfd();
    fd_tmp.events = POLLIN;
    tab_fd.push_back(fd_tmp);
    //////////main loop//////////
    while (1)
    {
        poll(tab_fd.data(), tab_fd.size(), 5000);
        if (tab_fd[0].revents == POLLIN)
        {
            fd_tmp.fd = accept(tab_fd[0].fd, NULL, NULL);
            fd_tmp.events = POLLIN;
            tab_fd.push_back(fd_tmp);
            tmp_user.setFD(fd_tmp.fd);
            tmp_user.setCurrentState(WAITING_FOR_APPROVAL);
            users.push_back(tmp_user);
            std::cout << "New Client" << std::endl;
        }
        /*else if (tab_fd[1].revents == POLLIN)
        {
            memset(buffer, 0, sizeof(buffer));
            if (recv(tab_fd[1].fd, buffer, 512, MSG_DONTWAIT) != -1)
            {
                str.append(buffer);
                if (users[0].getCurrentState() != ACCEPTED && users[0].process_cmd(str) == ACCEPTED)
                    send(tab_fd[1].fd, users[0].getAnswer().c_str(), users[0].getAnswerSize(), MSG_DONTWAIT | MSG_NOSIGNAL);
                //if (users[0].process_cmd(str) == ACCEPTED)
                   // send(tab_fd[1].fd, users[0].getAnswer().c_str(), users[0].getAnswerSize(), MSG_DONTWAIT | MSG_NOSIGNAL);
                //valid answer for connexion with no parsing//
                //send(tab_fd[1].fd, "001 vladplk :Welcome to my Network vladplk\r\n", 56, MSG_CONFIRM);
                str.clear();
                memset(buffer, 0, sizeof(buffer));
                users[0].getAnswer().clear();
            }
        }*/
        else
        {
            for (it = tab_fd.begin() + 1; it != tab_fd.end(); it++)
            {
                //std::cout << "fd in tab with iterator : " << it->fd << "fd in tab without : " << tab_fd[1].fd << std::endl;
                if (it->revents == POLLIN)
                {
                    memset(buffer, 0, sizeof(buffer));
                    if (recv(it->fd, buffer, 512, MSG_DONTWAIT) != -1)
                    {
                        str.append(buffer);
                        if (users[it->fd - 4].getCurrentState() != ACCEPTED && users[it->fd - 4].process_cmd(str) == ACCEPTED)
                        {
                            send(it->fd, users[it->fd - 4].getAnswer().c_str(), users[it->fd - 4].getAnswerSize(), MSG_DONTWAIT | MSG_NOSIGNAL);
                        }
                        //if (users[0].process_cmd(str) == ACCEPTED)
                           // send(tab_fd[1].fd, users[0].getAnswer().c_str(), users[0].getAnswerSize(), MSG_DONTWAIT | MSG_NOSIGNAL);
                        //valid answer for connexion with no parsing//
                        //send(tab_fd[1].fd, "001 vladplk :Welcome to my Network vladplk\r\n", 56, MSG_CONFIRM);
                        str.clear();
                        memset(buffer, 0, sizeof(buffer));
                        users[it->fd - 4].getAnswer().clear();
                    }
                }
            }
        }
    }
    //////////main loop//////////
}