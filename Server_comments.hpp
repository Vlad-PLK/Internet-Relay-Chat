/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_comments.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:13:00 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/28 09:43:31 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_COMMENTS_HPP
# define SERVER_COMMENTS_HPP

# define ERR_NEEDMOREPARAMS(nickname, cmd) "461 " + nickname + " " + cmd + ": Not enough parameters given\r\n"
# define ERR_ALREADYREGISTERED(username) "462 " + username + " :You may not reregister\r\n"
# define ERR_PASSWDMISMATCH(username) "464 " + username + " :Password incorrect\r\n"

#endif