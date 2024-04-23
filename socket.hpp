/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:59:54 by vpolojie          #+#    #+#             */
/*   Updated: 2024/04/23 17:12:05 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

typedef struct s_init_sock
{
	int                	sockfd;
	int					sock_opt;
	struct sockaddr_in 	addr;
}t_init_sock;

typedef struct s_user
{
	std::string			username;
	std::string			nickname;
	int					admin;
	std::vector<std::string> cmds;
}t_user;


class Message  {
private:
	std::string buffer;
public:
	int is_command_buffer(); // si \r\n dans buffer
};

void    ft_init_socket(int port);

#endif