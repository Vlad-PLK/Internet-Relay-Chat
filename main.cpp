/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 08:39:14 by vpolojie          #+#    #+#             */
/*   Updated: 2024/04/24 09:18:48 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "SocketServer.hpp"

int main(int argc, char **argv)
{
    if (argc == 3)
        ft_init_server_socket(atoi(argv[1]), argv[2]);
    else
        std::cout << "Error : incorrect number of arguments, "
                    "impossible to connect to the server" << std::endl;
}