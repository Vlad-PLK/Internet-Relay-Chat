/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 08:46:58 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/16 07:07:38 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketServer.hpp"
#include "User.hpp"
#include "Command.hpp"

void    main_loop(SocketServer &main_socket)
{
	///////////array of fds part///////////
	std::vector<struct pollfd> 				tab_fd;
	std::vector<struct pollfd>::iterator	it;
	struct pollfd       					fd_tmp;
	///////////array of fds part///////////

	///////////users///////////
	std::vector<std::string>				params;
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
			tmp_user = new User(fd_tmp.fd, NOT_ADMIN, REJECTED);
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
				try
				{
					if (it->revents & POLLIN)
						main_socket.getAllUsers()[i]->parsing_and_handle(main_socket);
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << '\n';
					main_socket.getAllUsers()[i]->setCurrentState(QUIT);
				}
				i++;
			}
		}
		int state;
		for (std::vector<User *>::iterator itU = main_socket.getAllUsers().begin(); itU != main_socket.getAllUsers().end(); itU++)
		{
			if ((*itU)->getCurrentState() == QUIT)
			{
				state = ACCEPTED;
				tab_fd.erase(tab_fd.begin() + (std::distance(main_socket.getAllUsers().begin(), itU) + 1));
				if (itU + 1 ==  main_socket.getAllUsers().end())
					state = REJECTED;
				close((*itU)->getFD());
				delete ((*itU));
				itU = main_socket.getAllUsers().erase(itU);
				if (state == REJECTED)
					break ;
			}
		}
	}
	//////////main loop//////////
}