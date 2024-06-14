/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:46:58 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/14 02:01:14 by vpolojie         ###   ########.fr       */
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
			memset(&fd_tmp, 0, sizeof(fd_tmp));
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
			int i = 0;
			for (it = tab_fd.begin() + 1; it != tab_fd.end(); it++)
			{
				if (it->revents & POLLIN)
					main_socket.getAllUsers()[i]->parsing_and_handle(main_socket);
				i++;
				// this is case if nc quit with ctrl-c or with an unknown method //
				//else if (it->revents & POLLHUP)
					//quit//
				
			}
			for (std::vector<User *>::iterator itU = main_socket.getAllUsers().begin(); itU != main_socket.getAllUsers().end(); itU++)
			{
				//std::cout << "user vector size before delete : " << main_socket.getAllUsers().size() << std::endl;
				if ((*itU)->getCurrentState() == QUIT)
				{
					close((*itU)->getFD());
					for (it = tab_fd.begin(); it != tab_fd.end(); it++)
					{
						if (it->fd == (*itU)->getFD())
							it = tab_fd.erase(it);
					}
					delete ((*itU));
					itU = main_socket.getAllUsers().erase(itU);
				}
				//std::cout << "user vector size after delete : " << main_socket.getAllUsers().size() << std::endl;
			}
		}
	}
	//////////main loop//////////
}