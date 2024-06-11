#include "../Command.hpp"

void modeInvite(SocketServer *server, User *user, Channel *channel, std::string arg, std::string add)
{
    (void)arg;
    (void)server;

    // channel->setMode('i', 1);
    // std::cout << "Channel modes :" << channel->getModes() << std::endl;
    for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
    {
        if (add == "+")
            (*itUser)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+i"));
        else
            (*itUser)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-i"));
    }
    // for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
    // {
    // 	if (add)
    // 		(*itOp)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+i"));
    // 	else
    // 		(*itOp)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-i"));
    // }
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
    // for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
    // {
    // 	if (add)
    // 		(*itOp)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+t"));
    // 	else
    // 		(*itOp)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-t"));
    // }
}

void modeKey(SocketServer *server, User *user, Channel *channel, std::string arg, std::string add)
{
    (void)server;

    if (add == "+" && !arg.empty())
    {
        channel->setPassword(arg);
        for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
            (*itUser)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+k", arg));
        // for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
        //     (*itOp)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+k", param[pos]));
    }
    else if (add == "+")
        user->usr_send((ERR_NEEDMOREPARAMS(user->getNickname(), "MODE")));
    else
    {
        channel->setPassword("");
        for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
            (*itUser)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-k"));
        // for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
        //     (*itOp)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-k"));
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
                // for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
                //     (*itOp)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+o", param[pos]));
            }
            else if (add == "-" && channel->setOperators(*user_target, false))
            {
                for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
                    (*itUser)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-o", arg));
                // for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
                //     (*itOp)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-o", param[pos]));
            }
        }
    }
}

void modeLimit(SocketServer *server, User *user, Channel *channel, std::string arg, std::string add)
{
    (void)server;

    // std::cout << "position = " << pos << "|| arg :" << arg << "add = " << add << std::endl;
    if (add == "+") // mode +l
    {
        if ((int)arg.size() < 1 || arg.empty()) // if /mode +l but no number associated with the command
            user->usr_send((ERR_NEEDMOREPARAMS(user->getNickname(), "MODE")));
        else // if /mode +l and number associated to the command
        {
            std::cout << "\nAVANT limit =" << channel->getLimit() << std::endl;
            int limit = atoi((arg).c_str());
            if (limit > 0 && limit >= (int)(channel->getChannelUsers().size()))
            {
                std::cout << "\nINSIDE_IF" << std::endl;
                channel->setLimit(limit);
                for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
                    (*itUser)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+l", arg));
            }
            std::cout << "\nAPRES limit =" << channel->getLimit() << std::endl;
        }
    }
    else // if /mode -l
    {
        channel->setLimit(-1);
        for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
            (*itUser)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-l"));
        std::cout << "\nAPRES limit =" << channel->getLimit() << std::endl;
        // for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
        //     (*itOp)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+t"));
    }
}

void mode(User &user, SocketServer &server, std::vector<std::string> &params)
{
    if (!params.size())
    {
        user.usr_send((ERR_NEEDMOREPARAMS(user.getNickname(), "MODE")));
        return;
    }
    std::string target = params[0];
    if (!server.findChannel(target))
    {
        user.usr_send((ERR_NOSUCHCHANNEL(user.getNickname(), target)));
        return;
    }
    else
    {
        Channel *channel = server.getChannel(target);
        //std::cout << "\nParams SIZE = " << (int)params.size() << std::endl;
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
                else if (current.size() != 0)
                    modes_arg.push_back(current);
                    // besoin de savoir comment push_back ICI sur le modesMinus_arg
                    // ou alors avoir un seul vecteur pour les + et -, et savoir comment index le bon arg au bon mode
            }
            size_t i = modes.size() - modes_arg.size();
            for (size_t count = 0; count != i; count++)
                modes_arg.push_back("NULL"); 
            // ordre des push des args
            // quit
            // part message sur le channel
            // leaks
            // kick
            std::cout << "modes : " << modes << std::endl;
            for (size_t k = 0; k < modes_arg.size(); k++)
            {
                std::cout << "modes sign : " << sign[k] << std::endl;
                std::cout << "modes arg : " << modes_arg[k] << std::endl;
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
            std::cout << "modes of the channel : " << channel->getModes() << std::endl;
        }
        else
            user.usr_send((ERR_CHANOPRIVSNEEDED(user.getNickname(), channel->getTitle())));
    }
}