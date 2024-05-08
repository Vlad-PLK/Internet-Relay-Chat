/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:46:58 by vpolojie          #+#    #+#             */
/*   Updated: 2024/04/26 08:41:28 by vpolojie         ###   ########.fr       */
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
    char                buffer[512];
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
        for (it = tab_fd.begin()++; it != tab_fd.end(); it++)
        {
            if (it->revents == POLLIN)
            {
                // users.recv();
                // if (users.has_buffer_command())
                // {
                //     std::cout << "IF 1" << std::endl;
                //     std::vector<std::string> cmd = users.get_command();
                //     handle_commad(user, cmd)
                // }
                memset(buffer, 0, sizeof(buffer));
                if (recv(it->fd, buffer, 512, MSG_DONTWAIT) != -1)
                {
                    std::cout << "IF 2" << std::endl;
                    str.append(buffer);
                    users.back().process_cmd(str);
                    send(it->fd, "001 tvinci :Welcome to my Network tvinci\r\n", 44, MSG_CONFIRM);
                    // send(it->fd, users.back().getAnswer().c_str(), users.back().getAnswer().size(), 0);
                    str.clear();
                }
                else
                    std::cout << "";
            }
        }
    }
    //////////main loop//////////
}