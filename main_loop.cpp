/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:46:58 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/12 09:13:14 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketServer.hpp"
#include "User.hpp"

void    main_loop(SocketServer &main_socket)
{
	///////////array of fds part///////////
	std::vector<struct pollfd> 				tab_fd;
	std::vector<struct pollfd>::iterator	it;
	struct pollfd       					fd_tmp;
	///////////array of fds part///////////

	///////////buffer for read///////////
	char                					buffer[513];
	ssize_t             					read_value;
	std::string 							str;
	///////////buffer for read///////////

	///////////users///////////
	std::vector<User> 						users;
	std::vector<User *>::iterator 			user_it;
	User              						*tmp_user;
	///////////users///////////

	/* push of the main socket in the fds array */
	fd_tmp.fd = main_socket.getSockfd();
	fd_tmp.events = POLLIN;
	tab_fd.push_back(fd_tmp);

	//////////main loop//////////
	while (1)
	{
		/* function to receive data from fds with I/O in non blocking mode */
		poll(tab_fd.data(), tab_fd.size(), 5000);

		/* event if there is a new connexion on the main socket */
		if (tab_fd[0].revents == POLLIN)
		{
			fd_tmp.fd = accept(tab_fd[0].fd, NULL, NULL);
			fd_tmp.events = POLLIN;
			tab_fd.push_back(fd_tmp);
			tmp_user = new User(fd_tmp.fd, NOT_ADMIN, WAITING_FOR_APPROVAL);
			main_socket.addUser(tmp_user);
			//users.push_back(*tmp_user);
		}
		/* other events received from all users of the server */
		else
		{
			/* for loop to check for all events in the fd arrays so for all existing users */
			for (it = tab_fd.begin() + 1; it != tab_fd.end(); it++)
			{
				if (it->revents == POLLIN)
				{
					memset(buffer, 0, sizeof(buffer));
					/* if there is a new message */
					read_value = recv(it->fd, buffer, 512, MSG_DONTWAIT);
					if (read_value != -1)
					{
						buffer[read_value] = 0;
						str.append(buffer);
					   
						/* parse the command, process and send the answer*/
						main_socket.getAllUsers()[it->fd - 4]->process_cmd(str, main_socket);
						/* clear all buffers and strings from previous message */
						str.clear();
					}
				}
			}
		}
	}
	//////////main loop//////////
}