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
    if (check_nickname_in_use(params[0], server.getAllUsers()) == 1)
    {
		srand(time(0));
		str = ft_itoa(rand() % 1000);
		if (check_nickname_in_use(params[0].append(str), server.getAllUsers()) == 0)
        	user.setNickname(params[0]);
    }
    else if (check_nickname_validity(params.front()) == 1)
        user.usr_send(ERR_ERRONEUSNICKNAME(params.front()));
    else if (params.front().size() == 0)
        user.usr_send(ERR_NONICKNAMEGIVEN());
    else
        user.setNickname(params.front());
}