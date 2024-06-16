/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 10:14:57 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/16 06:56:54 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Command.hpp"

int	ft_nbn(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

void	ft_putnbr(int nb, int *i, char *str)
{
	if (nb == -2147483648)
	{
		str[0] = '-';
		(*i)++;
		ft_putnbr(21474, i, str);
		ft_putnbr(83648, i, str);
	}
	else if (0 <= nb && nb <= 9)
		str[(*i)++] = nb + '0';
	else if (nb < 0)
	{
		str[0] = '-';
		(*i)++;
		ft_putnbr(nb *(-1), i, str);
	}
	else
	{
		ft_putnbr(nb / 10, i, str);
		ft_putnbr(nb % 10, i, str);
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = 0;
	if (n < 0)
		str = (char *)malloc((ft_nbn(n) + 2) * sizeof(char));
	else
		str = (char *)malloc((ft_nbn(n) + 1) * sizeof(char));
	if (!str)
		return (0);
	if (n == 0)
		str[0] = '0';
	ft_putnbr(n, &i, str);
	str[i] = '\0';
	return (str);
}


int check_nickname_in_use(std::string &nick, const std::vector<User *> &users)
{
    for (size_t i = 0; i != users.size(); i++)
	{
        if (nick == users[i]->getNickname())
            return (1);
    }
    return (0);
}

int check_nickname_validity(const std::string &nick)
{
    if (nick.find("#") != std::string::npos 
        || nick.find(":") != std::string::npos 
        || nick.find(" ") != std::string::npos
        || nick.find("&") != std::string::npos)
    {
        return (1);
    }
    return (0);
}

void					nick(User &user, SocketServer &server, std::vector<std::string> &params)
{
	std::string str;
	std::string oldnick;
	if (user.getCurrentState() == ACCEPTED || user.getCurrentState() == ALREADY_REGISTRED)
	{
		if (user.getCurrentState() == ALREADY_REGISTRED)
		{
			oldnick = user.getNickname();
			user.usr_send("You've already register, but here's your new request\r\n");
		}
		if (params.front().size() == 0)
    	    user.usr_send(ERR_NONICKNAMEGIVEN());
		else if (params.size() > 1 && isNotSpace(params, 1) == 1)
			user.usr_send("\nTOO MUCH PARAMS FOR NICK COMMAND\r\n");
		else if (params.size() == 1 || (params.size() > 1 && isNotSpace(params, 1) == 0))
		{
			if (check_nickname_in_use(params[0], server.getAllUsers()) == 1)
    		{
				srand(time(0));
				str = ft_itoa(rand() % 1000);
				if (check_nickname_in_use(params[0].append(str), server.getAllUsers()) == 0)
    		    	user.setNickname(params[0]);
    		}
    		else if (check_nickname_validity(params.front()) == 1)
    		    user.usr_send(ERR_ERRONEUSNICKNAME(params.front()));
    		else
    		    user.setNickname(params.front());
			if (user.getCurrentState() == ALREADY_REGISTRED)
				user.usr_send(":" + oldnick + " NICK " + params[0] + "\r\n");
		}
	}
	else if (user.getCurrentState() == WAITING_FOR_APPROVAL)
		user.usr_send("\nWAITING FOR OTHER COMMANDS FIRST\r\n");
}