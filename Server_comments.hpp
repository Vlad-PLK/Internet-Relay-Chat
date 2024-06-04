/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server_comments.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:13:00 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/04 11:09:31 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_COMMENTS_HPP
# define SERVER_COMMENTS_HPP

# define ERR_NEEDMOREPARAMS(user_nickname, cmd) "461 " + user_nickname + " " + cmd + " :Not enough parameters given\r\n"

# define ERR_CHANNELISFULL(user_nickname, channel_title) ":localhost 471 " + user_nickname + " " + channel_title + " :Cannot join channel (+l)\r\n"
# define ERR_INVITEONLYCHAN(user_nickname, channel_title) ":localhost 473 " + user_nickname + " " + channel_title + " :Cannot join channel (+i)\r\n"
# define ERR_BANNEDFROMCHAN(user_nickname, channel_title) ":localhost 474 " + user_nickname + " " + channel_title + " :Cannot join channel (+b)\r\n"
# define ERR_BADCHANNELKEY(user_nickname, channel_title) ":localhost 475 " + user_nickname + " " + channel_title + " :Cannot join channel (+k)\r\n"

# define RPL_JOIN(user_nickname, channel_title) ":" + user_nickname + " JOIN " + channel_title + "\r\n"
# define RPL_NAMREPLY(user_nickname, symbol, channel_title, all_members) ":localhost 353 " + user_nickname + " " + symbol + " " + channel_title + " :" + all_members + "\r\n"

# define RPL_PART(user_nickname, channel_title, reason) ":" + user_nickname + " PART " + channel_title + " " + reason +"\r\n"
# define ERR_NOSUCHCHANNEL(user_nickname, channel_title) ":localhost 404 " + user_nickname + " " + channel_title + " :No such channel\r\n"
# define ERR_NOTONCHANNEL(user_nickname, channel_title) ":localhost 442 " + user_nickname + " " + channel_title + " :You are not on that channel\r\n"

# define RPL_TOPIC(user_nickname, channel_title, channel_topic) ":localhost 332 " + user_nickname + " " + channel_title + " :" + channel_topic + "\r\n"
# define RPL_NOTOPIC(user_nickname, channel_title) ":localhost 331 " + user_nickname + " " + channel_title + " :No topic is set\r\n"
# define ERR_CHANOPRIVSNEEDED(user_nickname, channel_title) ":localhost 482 " + user_nickname + " " + channel_title + " :You're not channel operator\r\n"
# define RPL_ENDOFNAMES(user_nickname, channel_title) ":localhost 366 " + user_nickname + " " + channel_title + " :End of NAMES list.\r\n"

# define RPL_KICK(user_nickname, channel_title, kicked_user, reason) ":" + user_nickname + " KICK " + channel_title + " " + kicked_user + " " + reason + "\r\n"
# define ERR_USERNOTINCHANNEL(user_nickname, channel_title) ":localhost 441 " + user_nickname + " " + channel_title + " :They aren't on that channel\r\n"

# define RPL_INVITING(user_nickname, target, channel_title) ":localhost 341 " + user_nickname + " " + target + " " + channel_title + "\r\n"
# define RPL_INVITE(user_nickname, target, channel_title) ":" + user_nickname + " INVITE " + target + " " + channel_title + "\r\n"
# define ERR_USERONCHANNEL(user_nickname, target, channel_title) ":localhost 443 " + user_nickname + " " + target + " " + channel_title + " :is already on channel\r\n"
# define ERR_NOSUCHNICK(user_nickname, target) ":localhost 401 " + user_nickname + " " + target + " :No such nick/channel\r\n"

# define RPL_CHANGECHANNELMODE(user_nickname, channel_title, mode) ":" + user_nickname + " MODE " + channel_title + " " + mode + "\r\n"
# define RPL_CHANGECHANNELMODEWITHPARAM(user_nickname, channel_title, mode, param) ":" + user_nickname + " MODE " + channel_title + " " + mode + " " + param + "\r\n"

# define ERR_ALREADYREGISTERED(username) "462 " + username + " :You may not reregister\r\n"
# define ERR_PASSWDMISMATCH(username) "464 " + username + " :Password incorrect\r\n"
# define ERR_NICKNAMEINUSE(nickname) "433 * " + nickname + " :Nickname is already in use\r\n"
# define ERR_ERRONEUSNICKNAME(nickname) "432 " + nickname + " " + nickname + " :Erroneus nickname\r\n"
# define ERR_NONICKNAMEGIVEN() "431 client :No nickname given\r\n"

#endif