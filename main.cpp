/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 08:39:14 by vpolojie          #+#    #+#             */
/*   Updated: 2024/04/16 08:54:08 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        std::cout << argv[1] << ": The port number "
                 "on which your IRC server will be "
                "listening to for incoming "
                 "IRC connections" << std::endl;
        std::cout << argv[2] << ": The connection password. "
        "It will be needed by any IRC "
        "client that tries "
        "to connect to your server." << std::endl;
    }
    else
        std::cout << "Error : incorrect number of arguments, "
                    "impossible to connect to the server" << std::endl;
}