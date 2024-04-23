/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 08:39:14 by vpolojie          #+#    #+#             */
/*   Updated: 2024/04/23 08:28:17 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include "socket.hpp"
#include <cstring>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc == 3)
        ft_init_socket(atoi(argv[1]));
    else
        std::cout << "Error : incorrect number of arguments, "
                    "impossible to connect to the server" << std::endl;
}