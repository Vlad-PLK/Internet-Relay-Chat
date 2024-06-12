#include "../Command.hpp"

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

    if (add == "+" && !arg.empty())
    {
        channel->setPassword(arg);
        for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
            (*itUser)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+k", arg));
    }
    else if (add == "+")
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
    if (!arg.size())
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
        if ((int)arg.size() < 1 || arg.empty())
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

void mode(User &user, SocketServer &server, std::vector<std::string> &params)
{
    if (!params.size())
    {
        user.usr_send((ERR_NEEDMOREPARAMS(user.getNickname(), "MODE")));
        return;
    }
    if (params[0][0] != '#')
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
    else if (!server.findChannel(params[0]))
    {
        user.usr_send((ERR_NOSUCHCHANNEL(user.getNickname(), params[0])));
        return;
    }
    else
    {
        Channel *channel = server.getChannel(params[0]);
        if (params.size() < 2 || params[1].empty())
            return;
        if (channel->userIsOperator(user.getNickname()))
        {
            std::string modes;
            std::vector<std::string> modes_arg;
            std::vector<std::string> sign;
            bool add = true;
            std::string prev;
            std::map<char, void (*)(SocketServer *server, User *user, Channel *channel, std::string arg, std::string add)> mode;
            mode['i'] = modeInvite;
            mode['t'] = modeTopic;
            mode['k'] = modeKey;
            mode['o'] = modeOp;
            mode['l'] = modeLimit;
            for (size_t i = 1; i < params.size(); i++)
            {
                std::string current = params[i];
                if (current[0] == '+' || current[0] == '-')
                {
                    add = (current[0] == '+');
                    for (size_t k = 1; k < current.size(); k++)
                    {
                        std::string md;
                        std::string tmp_sign;
                        md = current[k];
                        if (add)
                            tmp_sign = '+';
                        else
                            tmp_sign = '-';
                        if (prev.find(md) == std::string::npos)
                        {
                            sign.push_back(tmp_sign);
                            modes.append(md);
                            prev.append(md);
                        }
                        md.clear();
                        tmp_sign.clear();
                    } 
                }
            }
            size_t arg_index = 2;
            for (size_t i = 0; i != modes.size(); i++)
            {
                if ((sign[i] == "+" && (modes[i] != 'i' && modes[i] != 't'))
                    || (sign[i] == "-" && modes[i] == 'o'))
                {
                    modes_arg.push_back(params[arg_index]);
                    arg_index++;
                }
                else
                    modes_arg.push_back("NULL");
            }
            for (size_t index = 0; index < modes.size(); index++)
            {
                if (mode.find(modes[index]) != mode.end())
                {
                    mode[modes[index]](&server, &user, channel, modes_arg[index], sign[index]);
                    if (sign[index] == "+")
                        channel->setMode(modes[index], true);
                    else
                        channel->setMode(modes[index], false);
                }
            }
        }
        else
            user.usr_send((ERR_CHANOPRIVSNEEDED(user.getNickname(), channel->getTitle())));
    }
}
