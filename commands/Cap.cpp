/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:14:52 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/05 09:09:07 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

void					cap(User &user, SocketServer &server, std::vector<std::string> &params)
{
    (void)params;
    (void)server;
    user.setCurrentState(WAITING_FOR_APPROVAL);
}