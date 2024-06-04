/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:58:31 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/30 13:59:09 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

void modeInvite(SocketServer *server, User *user, std::vector<std::string> &params, bool add)
{
    std::string target = params[0];
	Channel *channel = server->getChannel(target);
}

void    mode(User &user, Channel &channel_void, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel_void;
    (void)server;
    if (!params.size())
    {
        user.usr_send((ERR_NEEDMOREPARAMS(user.getNickname(), "MODE")).c_str());
        return ;
    }
    std::string target = params[0];
    if (target[0] == '#')
    {
        if (!server.findChannel(target))
        {
            user.usr_send((ERR_NOSUCHCHANNEL(user.getNickname(), target)).c_str());
            return;
        }
        else
        {
            if (params.size() < 2 || params[1].empty())
                return ;
            else if (server.getChannel(target)->userIsOperator(user.getNickname()))
            {
                Channel *channel = server.getChannel(target);
                std::map<char, void(*)(SocketServer *server, User *user, std::vector<std::string>& cmd, bool add)> mode;
                mode['i'] = modeInvite;
                // mode['t'] = modeTopic;
                // mode['k'] = modePass;
                // mode['o'] = modeOp;
                // mode['l'] = modeLimit;
                
                bool add;
                for (int i = 1; i < params.size(); i++)
                {
                    std::string current = params[i];
                    if (current[0] == '+')
                    {
                        add = true;
                    }
                    else if (current[0] == '-')
                    {
                        add = false;
                    }
                    for (size_t j = 1; j < current.length(); j++)
                    {
                        char mode_char = current[j];
                        if (mode.find(mode_char) != mode.end())
                        {
                            std::vector<std::string> mode_args;
                            while (i + 1 < params.size() && params[i + 1][0] != '+' && params[i + 1][0] != '-')
                                mode_args.push_back(params[++i]);
                            mode[mode_char](&server, &user, mode_args, add);
                        }
                    }
                }
            }
            else
                user.usr_clean()
        }
    }
}