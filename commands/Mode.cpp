/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 22:26:06 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/16 23:05:24 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"
#include "Mode.hpp"

ModeTool::ModeTool()
{
}

ModeTool::~ModeTool()
{
}


void modeInvite(SocketServer *server, User *user, Channel *channel, std::string arg, std::string add)
{
	(void)arg;
	(void)server;

	for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
	{
		if (add == "+")
			(*itUser)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+i"));
		else
			(*itUser)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-i"));
	}
}

void modeTopic(SocketServer *server, User *user, Channel *channel, std::string arg, std::string add)
{
	(void)arg;
	(void)server;

	for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
	{
		if (add == "+")
			(*itUser)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+t"));
		else
			(*itUser)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-t"));
	}
}

void modeKey(SocketServer *server, User *user, Channel *channel, std::string arg, std::string add)
{
	(void)server;

	if (add == "+" && arg != "NULL")
	{
		channel->setPassword(arg);
		for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
			(*itUser)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+k", arg));
	}
	else if (add == "+" && arg == "NULL")
		user->usr_send((ERR_NEEDMOREPARAMS(user->getNickname(), "MODE")));
	else
	{
		channel->setPassword("");
		for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
			(*itUser)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-k"));
	}
}

void modeOp(SocketServer *server, User *user, Channel *channel, std::string arg, std::string add)
{
	if (arg == "NULL")
		user->usr_send(ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"));
	else
	{
		if (!channel->userIsMember(arg) && !channel->userIsOperator(arg))
			user->usr_send(ERR_USERNOTINCHANNEL(arg, channel->getTitle()));
		else
		{
			User *user_target = server->getUser(arg);
			if (add == "+" && channel->setOperators(*user_target, true))
			{
				for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
					(*itUser)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+o", arg));
			}
			else if (add == "-" && channel->setOperators(*user_target, false))
			{
				for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
					(*itUser)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-o", arg));
			}
		}
	}
}

void modeLimit(SocketServer *server, User *user, Channel *channel, std::string arg, std::string add)
{
	(void)server;

	if (add == "+")
	{
		if (arg == "NULL")
			user->usr_send((ERR_NEEDMOREPARAMS(user->getNickname(), "MODE")));
		else
		{
			int limit = atoi((arg).c_str());
			if (limit > 0 && limit >= (int)(channel->getChannelUsers().size()))
			{
				channel->setLimit(limit);
				for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
					(*itUser)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+l", arg));
			}
		}
	}
	else
	{
		channel->setLimit(-1);
		for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
			(*itUser)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-l"));
	}
}

void mode_user(User &user, SocketServer &server, std::vector<std::string> &params)
{
	if (!server.findUser(params[0]))
		user.usr_send(ERR_NOSUCHNICK(user.getNickname(), params[0]));
	else if (user.getNickname() != params[0])
		user.usr_send(ERR_USERDONTMATCH(user.getNickname()));
	else if (params.size() == 1)
		user.usr_send(RPL_UMODEIS(user.getNickname(), "+i"));
	else
		user.usr_send(":" + user.getNickname() + " MODE " + user.getNickname() + " " + params[1] + "\r\n");
}

void mode_chan_set_modes(ModeTool &tool, std::vector<std::string> &params)
{
	for (size_t i = 1; i < params.size(); i++)
	{
		tool.current = params[i];
		//add multiple minus and pluq
		if (tool.current[0] == '+' || tool.current[0] == '-')
		{
			tool.add = (tool.current[0] == '+');
			for (size_t k = 1; k < tool.current.size(); k++)
			{
				tool.tmp_mode = tool.current[k];
				if (tool.add)
					tool.tmp_sign = '+';
				else
					tool.tmp_sign = '-';
				if (tool.prev.find(tool.tmp_mode) == std::string::npos)
				{
					tool.sign.push_back(tool.tmp_sign);
					tool.modes.append(tool.tmp_mode);
					tool.prev.append(tool.tmp_mode);
				}
				tool.tmp_mode.clear();
				tool.tmp_sign.clear();
			} 
		}
	}
}

void mode_chan_set_modes_args(ModeTool &tool, std::vector<std::string> &params)
{
	size_t arg_index = 2;
	for (size_t i = 0; i != tool.modes.size(); i++)
		tool.modes_arg.push_back("NULL");
	for (size_t i = 0; i != tool.modes.size(); i++)
	{
		if ((tool.sign[i] == "+" && (tool.modes[i] != 'i' && tool.modes[i] != 't'))
			|| (tool.sign[i] == "-" && tool.modes[i] == 'o'))
		{
			//std::cout << params.size() << arg_index << std::endl;
			if (params.size() >= arg_index + 1)
				tool.modes_arg[i] = params[arg_index];
			arg_index++;
		}
	}
}

void mode_channel(User &user, SocketServer &server, std::vector<std::string> &params)
{
	Channel                 *channel;
	ModeTool				 tool;
	std::map<char, void (*)(SocketServer *server, User *user, Channel *channel, std::string arg, std::string add)> mode;

	tool.add = true;
	mode['i'] = modeInvite;
	mode['t'] = modeTopic;
	mode['k'] = modeKey;
	mode['o'] = modeOp;
	mode['l'] = modeLimit;
	channel = server.getChannel(params[0]);

	if (params.size() == 1)
		user.usr_send(RPL_CHANNELMODEIS(user.getNickname(), channel->getTitle(), channel->getModes()));
	else if (params.size() > 1 && channel->userIsOperator(user.getNickname()))
	{
		mode_chan_set_modes(tool, params);
		mode_chan_set_modes_args(tool, params);
		for (size_t index = 0; index < tool.modes.size(); index++)
		{
			if (mode.find(tool.modes[index]) != mode.end())
			{
				//std::cout << "mode name : " << tool.modes[index] << " mode sign : " << tool.sign[index]
				//	<< " mode arg : " << tool.modes_arg[index] << std::endl;
				mode[tool.modes[index]](&server, &user, channel, tool.modes_arg[index], tool.sign[index]);
				if (tool.sign[index] == "+")
					channel->setMode(tool.modes[index], true);
				else
					channel->setMode(tool.modes[index], false);
			}
		}
	}
	else
		user.usr_send((ERR_CHANOPRIVSNEEDED(user.getNickname(), channel->getTitle())));
}

void mode(User &user, SocketServer &server, std::vector<std::string> &params)
{
	if (params.size() == 0)
		user.usr_send((ERR_NEEDMOREPARAMS(user.getNickname(), "MODE")));
	else if (params.size() >= 1 && params[0][0] != '#')
		mode_user(user, server, params);
	else if (!server.findChannel(params[0]))
		user.usr_send((ERR_NOSUCHCHANNEL(user.getNickname(), params[0])));
	else
		mode_channel(user, server, params);
}
