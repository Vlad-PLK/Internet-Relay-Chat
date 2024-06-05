#include "../Command.hpp"

void modeInvite(User *user, Channel *channel, int pos, std::vector<std::string> &param, bool add)
{
    (void)param;
    (void)pos;
    for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
	{
		if (add)
			(*itUser)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+i"));
		else
		    (*itUser)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-i"));
	}
    for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
	{
		if (add)
			(*itOp)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+i"));
		else
			(*itOp)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-i"));
	}
}

void modeTopic(User *user, Channel *channel, int pos, std::vector<std::string> &param, bool add)
{
    (void)param;
    (void)pos;
    for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
	{
		if (add)
			(*itUser)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+t"));
		else
			(*itUser)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-t"));
	}
    for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
	{
		if (add)
			(*itOp)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+t"));
		else
			(*itOp)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-t"));
	}
}

void modePass(User *user, Channel *channel, int pos, std::vector<std::string> &param, bool add)
{
    if (add == true && !param[pos].empty())
    {
        channel->setPassword(param[pos]);
        for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
			(*itUser)->usr_send(RPL_CHANGECHANNELMODEWITHPARAM((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+k", param[pos]));
        for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
            (*itOp)->usr_send(RPL_CHANGECHANNELMODEWITHPARAM((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+k", param[pos]));
    }
    else if (add == true)
        user->usr_send((ERR_NEEDMOREPARAMS(user->getNickname(), "MODE")));
    else
    {
        channel->setPassword("");
        for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
			(*itUser)->usr_send(RPL_CHANGECHANNELMODEWITHPARAM((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-k", param[pos]));
        for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
            (*itOp)->usr_send(RPL_CHANGECHANNELMODEWITHPARAM((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-k", param[pos]));
    }
}

void modeOp(User *user, Channel *channel, int pos, std::vector<std::string> &param, bool add)
{
    if (!param.size())
        user->usr_send((ERR_NEEDMOREPARAMS(user->getNickname(), "MODE")).c_str());
    else
    {
        if (!channel->userIsMember(param[pos]) && !channel->userIsOperator(param[pos]))
            user->usr_send((ERR_USERNOTINCHANNEL(param[pos], channel->getTitle())).c_str());
        else
        {
            if (add && channel->setOperators(*user, add))
            {
                for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
                    (*itUser)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+o", param[pos]));
                for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
                    (*itOp)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+o", param[pos]));
            }
            else if (!add && channel->setOperators(*user, add))
            {
                for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
                    (*itUser)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-o", param[pos]));
                for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
                    (*itOp)->usr_send(RPL_REPLACECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "-o", param[pos]));
            }

        }
    }
}

void modeLimit(User *user, Channel *channel, int pos, std::vector<std::string> &param, bool add)
{
    if (add == true && param[pos].empty())
        user->usr_send((ERR_NEEDMOREPARAMS(user->getNickname(), "MODE")));
    else if (add == false)
    {
        channel->setLimit(-1);
        for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
            (*itUser)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+t"));
        for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
            (*itOp)->usr_send(RPL_CHANGECHANNELMODE((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+t"));
    }
    else
    {
        int limit = atoi((param[pos]).c_str());
        if (limit > 0 && limit >= (int)(channel->getChannelUsers().size() + channel->getChannelOperators().size()))    
            channel->setLimit(limit);
        for (std::vector<User *>::iterator itUser = channel->getChannelUsers().begin(); itUser != channel->getChannelUsers().end(); ++itUser)
			(*itUser)->usr_send(RPL_CHANGECHANNELMODEWITHPARAM((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+l", param[pos]));
        for (std::vector<User *>::iterator itOp = channel->getChannelOperators().begin(); itOp != channel->getChannelOperators().end(); ++itOp)
            (*itOp)->usr_send(RPL_CHANGECHANNELMODEWITHPARAM((user->getNickname() + "!" + user->getUsername() + "@localhost"), channel->getTitle(), "+l", param[pos]));
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
            else if (server.getChannel(target)->userIsOperator(user.getNickname()))
            {
                std::map<char, void(*)(User *user, Channel *channel, int pos, std::vector<std::string> &param, bool add)> mode;
                mode['i'] = modeInvite;
                mode['t'] = modeTopic;
                mode['k'] = modePass;
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
                        if (mode.find(mode_char) != mode.end() || prev.find(mode_char) != 0)
                        {
                            std::vector<std::string> mode_args;
                            while (i + 1 < (int)params.size() && params[i + 1][0] != '+' && params[i + 1][0] != '-')
                                mode_args.push_back(params[++i]);
                            mode[mode_char](&user, channel, j, mode_args, add);
                            if (mode_char != 'o')
                            {
                                prev += mode_char;
                                channel->setMode(mode_char, add);
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