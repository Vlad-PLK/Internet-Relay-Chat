#include "../Command.hpp"

void modeInvite(SocketServer *server, User *user, Channel *channel, int pos, std::vector<std::string> &param, bool add)
{
    (void)param;
    (void)pos;
    (void)server;

    // channel->setMode('i', 1);
    std::cout << "Channel modes :" << channel->getModes() << std::endl;
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

void modeTopic(SocketServer *server, User *user, Channel *channel, int pos, std::vector<std::string> &param, bool add)
{
    (void)param;
    (void)pos;
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

void modeKey(SocketServer *server, User *user, Channel *channel, int pos, std::vector<std::string> &param, bool add)
{
    (void)server;
    (void)pos;

    if (add == true && !param[0].empty())
    {
        channel->setPassword(param[0]);
        for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
			(*itUser)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+k", param[0]));
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

void modeOp(SocketServer *server, User *user, Channel *channel, int pos, std::vector<std::string> &param, bool add)
{
    if (!param.size())
        user->usr_send(ERR_NEEDMOREPARAMS(user->getNickname(), "MODE"));
    else
    {
        if (!channel->userIsMember(param[0]) && !channel->userIsOperator(param[0]))
            user->usr_send(ERR_USERNOTINCHANNEL(param[0], channel->getTitle()));
        else
        {
            User *user_target = server->getUser(param[0]);
            if (add && channel->setOperators(*user_target, add))
            {
                for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
                    (*itUser)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+o", param[0]));
                // for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
                //     (*itOp)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+o", param[pos]));
            }
            else if (!add && channel->setOperators(*user_target, add))
            {
                for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
                    (*itUser)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-o", param[0]));
                // for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
                //     (*itOp)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-o", param[pos]));
            }
        }
    }
}


void modeLimit(SocketServer *server, User *user, Channel *channel, int pos, std::vector<std::string> &param, bool add)
{
    (void)pos;
    (void)server;

    // std::cout << "position = " << pos << "|| param[0] :" << param[0] << "add = " << add << std::endl;
    if (add == true) //mode +l
    {
        if ((int)param.size() < 1 || param[0].empty()) // if /mode +l but no number associated with the command
            user->usr_send((ERR_NEEDMOREPARAMS(user->getNickname(), "MODE")));
        else // if /mode +l and number associated to the command
        {
            std::cout << "\nAVANT limit =" << channel->getLimit() << std::endl;
            int limit = atoi((param[0]).c_str());
            if (limit > 0 && limit >= (int)(channel->getChannelUsers().size()))
            {
                std::cout << "\nINSIDE_IF" << std::endl;
                channel->setLimit(limit);
                for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
                    (*itUser)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+l", param[0]));
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

void    mode(User &user, SocketServer &server, std::vector<std::string> &params)
{
    if (!params.size())
    {
        user.usr_send((ERR_NEEDMOREPARAMS(user.getNickname(), "MODE")));
        return ;
    }
    std::string target = params[0];
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
            if (params.size() < 2 || params[1].empty())
                return ;
            else if (channel->userIsOperator(user.getNickname()))
            {
                std::map<char, void(*)(SocketServer *server, User *user, Channel *channel, int pos, std::vector<std::string> &param, bool add)> mode;
                mode['i'] = modeInvite;
                mode['t'] = modeTopic;
                mode['k'] = modeKey;
                mode['o'] = modeOp;
                mode['l'] = modeLimit;
                
                bool add;
                for (int i = 1; i < (int)params.size(); i++)
                {
                    std::string prev;
                    std::string current = params[i];
                    if (current[0] == '+')
                    {
                        add = true;
                    }
                    else if (current[0] == '-')
                    {
                        add = false;
                    }
                    for (int j = 1; j < (int)current.length(); j++)
                    {
                        char mode_char = current[j];
                        std::cout << "\nCurrent[j] :" << current[j] << std::endl;
                        if (mode.find(mode_char) != mode.end() && prev.find(mode_char) == std::string::npos)
                        {
                            std::vector<std::string> mode_args;
                            while (i + 1 < (int)params.size() && params[i + 1][0] != '+' && params[i + 1][0] != '-')
                                mode_args.push_back(params[++i]);
                            std::cout << "\nJ = " << j << std::endl;
                            for (std::vector<std::string>::iterator it = mode_args.begin(); it != mode_args.end(); ++it)
                                std::cout << (*it) << std::endl;
                            mode[mode_char](&server, &user, channel, j, mode_args, add);
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
            else
                user.usr_send((ERR_CHANOPRIVSNEEDED(user.getNickname(), channel->getTitle())));
        }
    }
}