#include "../Command.hpp"

void modeInvite(SocketServer *server, User *user, Channel *channel, std::string arg, bool add)
{
    (void)arg;
    (void)server;

    // channel->setMode('i', 1);
    // std::cout << "Channel modes :" << channel->getModes() << std::endl;
    for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
    {
        if (add)
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

void modeTopic(SocketServer *server, User *user, Channel *channel, std::string arg, bool add)
{
    (void)arg;
    (void)server;

    for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
    {
        if (add)
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

void modeKey(SocketServer *server, User *user, Channel *channel, std::string arg, bool add)
{
    (void)server;

    if (add == true && !arg.empty())
    {
        channel->setPassword(arg);
        for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
            (*itUser)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+k", arg));
        // for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
        //     (*itOp)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+k", param[pos]));
    }
    else if (add == true)
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

void modeOp(SocketServer *server, User *user, Channel *channel, std::string arg, bool add)
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
            if (add && channel->setOperators(*user_target, add))
            {
                for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
                    (*itUser)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+o", arg));
                // for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
                //     (*itOp)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+o", param[pos]));
            }
            else if (!add && channel->setOperators(*user_target, add))
            {
                for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
                    (*itUser)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-o", arg));
                // for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
                //     (*itOp)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-o", param[pos]));
            }
        }
    }
}

void modeLimit(SocketServer *server, User *user, Channel *channel, std::string arg, bool add)
{
    (void)server;

    // std::cout << "position = " << pos << "|| arg :" << arg << "add = " << add << std::endl;
    if (add == true) // mode +l
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
    std::cout << "\narg :" << params[0] << std::endl;
    if (target[0] == '#')
    {
        if (!server.findChannel(target))
        {
            user.usr_send((ERR_NOSUCHCHANNEL(user.getNickname(), target)));
            return;
        }
        else
        {
            Channel *channel = server.getChannel(target);
            std::cout << "\nParams SIZE = " << (int)params.size() << std::endl;
            if (params.size() < 2 || params[1].empty())
            {
                std::cout << "\nPARAM < 2" << std::endl;
                return;
            }
            if (channel->userIsOperator(user.getNickname()))
            {
                std::string modesPlus;
                std::string modesMinus;
                std::vector<std::string> modesPlus_arg;
                std::vector<std::string> modesMinus_arg;
                bool add = true;
                std::string prev;

                std::map<char, void (*)(SocketServer *server, User *user, Channel *channel, std::string arg, bool add)> mode;
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
                            md = current[k];
                            if (prev.find(md) == std::string::npos)
                            {
                                if (add)
                                    modesPlus.append(md);
                                else
                                    modesMinus.append(md);
                                prev.append(md);
                            }
                            md.clear();
                        }
                    }
                    else if (current.size() != 0)
                    {
                        modesPlus_arg.push_back(current);
                        // besoin de savoir comment push_back ICI sur le modesMinus_arg
    
                        // ou alors avoir un seul vecteur pour les + et -, et savoir comment index le bon arg au bon mode
                    }
                }
                std::cout << "modesPlus : " << modesPlus << std::endl;
                for (size_t k = 0; k < modesPlus_arg.size(); k++)
                {
                    std::cout << "modes arg : " << modesPlus_arg[k] << std::endl;
                }
                for (size_t index = 0; index < modesPlus.size(); index++)
                {
                    if (mode.find(modesPlus[index]) != mode.end())
                        mode[modesPlus[index]](&server, &user, channel, modesPlus_arg[index], add);
                }
            }
            else
                user.usr_send((ERR_CHANOPRIVSNEEDED(user.getNickname(), channel->getTitle())));
        }
    }
}

/*else if (channel->userIsOperator(user.getNickname()))
            {
                std::map<char, void(*)(SocketServer *server, User *user, Channel *channel, std::string arg, bool add)> mode;
                mode['i'] = modeInvite;
                mode['t'] = modeTopic;
                mode['k'] = modeKey;
                mode['o'] = modeOp;
                mode['l'] = modeLimit;

                bool add = true;
                for (int i = 1; i < (int)params.size(); i++)
                {
                    std::cout << "\nSTART!" << std::endl;
                    std::string prev;
                    std::string current = params[i];
                    if (current[0] == '+' || current[0] == '-')
                    {
                        for (int j = 1; j < (int)current.length(); j++)
                        {
                            add = (current[0] == '+');
                            char mode_char = current[j];
                            std::cout << "\nCurrent[j] :" << current[j] << std::endl;
                            if (mode.find(mode_char) != mode.end() && prev.find(mode_char) == std::string::npos)
                            {
                                std::cout << "\nFOUND MODE_CHAR" << std::endl;
                                std::vector<std::string> arg;
                                int k = i;
                                while (k + 1 < (int)params.size() && params[k + 1][0] != '+' && params[k + 1][0] != '-')
                                {
                                    arg.push_back(params[++k]);
                                    std::cout << "\nARG ADDED" << std::endl;
                                }
                                int l_test = -1;
                                for (std::vector<std::string>::iterator it = arg.begin(); it != arg.end(); ++it)
                                    std::cout << "ARG[" << ++l_test << "] :" << (*it) << std::endl;
                                mode[mode_char](&server, &user, channel, arg[j], add);
                                if (mode_char != 'o')
                                {
                                    prev += mode_char;
                                    channel->setMode(mode_char, add);
                                    std::cout << "Channel modes" << " add = " << add << " :" << channel->getModes() << std::endl;
                                }
                            }
                        }
                    }
                }
            }
            else
                user.usr_send((ERR_CHANOPRIVSNEEDED(user.getNickname(), channel->getTitle())));*/