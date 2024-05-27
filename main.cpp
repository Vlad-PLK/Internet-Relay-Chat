/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 08:39:14 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/27 10:18:29 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketServer.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
        std::cout << "Error : incorrect number of arguments" << std::endl;
    else
    {
        // need to add port errors check -> invalid ports, forbidden etc //
        try
        {
            ft_init_server_socket(atoi(argv[1]), argv[2]);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }
}