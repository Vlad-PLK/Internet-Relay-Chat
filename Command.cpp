/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:45:37 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/29 09:35:26 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"
#include "SocketServer.hpp"
#include "Server_comments.hpp"

static const Command_Dictionnary cmds[] = {
    {"CAP LS", cap},
    {"PASS", pass},
    {"NICK", nick},
    {"USER", user},
	{"MODE", mode},
	{"WHOIS", whois},
	{"PING", ping},
    {"JOIN", join_bis}
};

void HandleCommand(Command &cmd, User &usr, Channel &chl, SocketServer &server)
{
	(void)chl;
    for (long unsigned int i = 0; i < sizeof(cmds) / sizeof(cmds[0]); i++)
    {
        if (cmd.getCmdName() == cmds[i].name)
            cmds[i].fct(usr, chl, server, cmd.getParams());
        // handle unknown commands ? //
    }
}

Command::Command()
{
}

Command::~Command(){}

void Command::setRawCommand(std::string &cmd)
{
    this->raw_command.assign(cmd);
}

void Command::setCmdName()
{
    return ;
}

void Command::setCmdParams()
{
    size_t  index = 0;

    if (this->raw_command[0] == ':')
       index = this->raw_command.find(' ', 0);
    this->cmd_name = this->raw_command.substr(index, this->raw_command.find(' ', index) - index);
    index = this->raw_command.find(' ', index);
    while (index <= this->raw_command.size())
    {
		if (this->raw_command[index + 1] != ':')
        {
            index++;
            this->params.push_back(this->raw_command.substr(index, this->raw_command.find(' ', index) - index));
            index = this->raw_command.find(' ', index);
        }
        else
        {
            index++;
            this->params.push_back(this->raw_command.substr(index + 2, std::string::npos));
            break ;
        }
	}
}

std::string const &Command::getRawCommand(void)
{
    return (this->raw_command);
}

std::string const &Command::getCmdName(void)
{
    return (this->cmd_name);
}

std::vector<std::string> &Command::getParams(void)
{
    return (this->params);
}

void    Command::clearCmd(void)
{
    this->raw_command.clear();
    this->cmd_name.clear();
    this->params.clear();
}

void					cap(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)params;
    (void)server;
    user.setCurrentState(WAITING_FOR_APPROVAL);
}

void					pass(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    if (server.getPassword() == params.front())
        user.setCurrentState(ACCEPTED);
    else
        user.setCurrentState(REJECTED);
}

void					nick(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)server;
    std::string answer;
    user.setNickname(params.front());
    if (user.getCurrentState() == REJECTED)
    {
        answer = ERR_PASSWDMISMATCH(user.getNickname());
        send(user.getFD(), answer.c_str(), answer.size(), MSG_DONTWAIT | MSG_NOSIGNAL);
        //send(user.getFD(), "ERROR: incorrect password\r\n", 28, MSG_DONTWAIT | MSG_NOSIGNAL);
    }
}

void					user(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)server;
    if (user.getCurrentState() == ACCEPTED)
    {
        user.setUsername(params.front());
        user.usr_send("001 " + user.getNickname() + " :Welcome to 42's Network " + user.getNickname() + "\r\n");
        user.usr_send("002 " + user.getNickname() + " :Your host is VPTV, running version lol.dev.c3plus\r\n");
        user.usr_send("003 " + user.getNickname() + " :This server was created 2024-05-28 10:11 CEST:+0200\r\n");
    }
}

void					whois(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)server;
    (void)params;
    user.usr_send("318 " + user.getUsername() + " " + user.getNickname() + " :END of /WHOIS list\r\n");
}

void					mode(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)server;
    (void)params;
    std::string answer;
    user.usr_send("221 " + user.getNickname() + " +i\r\n");
}

void					ping(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    (void)server;
    (void)params;
    user.usr_send("PONG " + params.front() + "\r\n");
}

std::vector<std::string>    joinSetters(std::string param)
{
    std::vector<std::string> res;
    std::stringstream ss(param); // Use stringstream to split the string
    std::string copy;
    while (std::getline(ss, copy, ','))
        res.push_back(copy);
    return res;
}

void                    join_bis(User &user, Channel &channel, SocketServer &server, std::vector<std::string> &params)
{
    (void)channel;
    //std::string answer;
    //if (params.empty())
    //{
    //    answer =
    //}
        //user.my_send((ERR_NEEDMOREPARAMS(user.getNickname(), "JOIN")).c_str(), (ERR_NEEDMOREPARAMS(user.getNickname(), "JOIN")).length(), 0);
        //user.my_send((ERR_NEEDMOREPARAMS(user.getNickname(), "JOIN")).c_str(), (ERR_NEEDMOREPARAMS(user.getNickname(), "JOIN")).length(), 0);
    
    // Setting up the channel_titles vector to store all the names given in the command
    std::vector<std::string> channels = joinSetters(params[0]);
    
    std::vector<std::string> passwords;
    if (params.size() > 1)
        passwords = joinSetters(params[1]);

    // Creating non existing channels
    for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); ++it)
    {
        if (!it->empty() && (*it)[0] != '#')
            it->insert(0, 1, '#'); // adds # as first character of the nickname
    }
    int i = -1;
    int j = 0;
    while (++i < (int)channels.size())
    {
        if (!server.findChannel(channels[i]))
        {
            if (j < (int)passwords.size())
            {
                if (!passwords[j].empty())
                {
                    server.addChannel(channels[i], passwords[j]);
                    server.getChannel(channels[i])->addUser(user);
                }
                else
                {
                    server.addChannel(channels[i]);
                    server.getChannel(channels[i])->addUser(user);
                }
                ++j;
            }
            else
            {
                // if less passwords than channel names
                server.addChannel(channels[i]); 
                server.getChannel(channels[i])->addUser(user);
            }
        }
    }
}