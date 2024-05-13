/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:42:46 by vpolojie          #+#    #+#             */
/*   Updated: 2024/05/13 11:16:41 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include "SocketServer.hpp"
#include "Command.hpp"
#include <iostream>
# define ACCEPTED 0
# define REJECTED 1
# define WAITING_FOR_APPROVAL 2
# define IS_ADMIN 3
# define NOT_ADMIN 4

class User
{
private:
    std::string                 username;
    std::string                 nickname;
    std::string                 server_password;
    int                         userfd;
    int                         admin_state;
    int                         current_state;
    std::string                 buffer;
    std::vector<Command>        cmds;
    std::string                 answer;

public:
    User(/* args */);
    User(int fd, int logstate);
    ~User();

    const std::string &getUsername(void) const;
    const std::string &getNickname(void) const;
    std::string &getAnswer(void);
    int                getAnswerSize(void) const;
    int                getFD(void) const;
    int                getCurrentState(void) const;
    void               setFD(int fd);
    void               setAnswer(void);
    void               setUsername(const std::string &uname);
    void               setNickname(const std::string &nname);
    void               setPassword(const std::string &pass);
    void               setCurrentState(int state);
    void               setAdminState(int state);

    int                process_cmd(std::string buffer);
    void               parse_buffer(std::string &buffer);
    void               parse_cmds();
    int                connexion_try(void);
};

std::ostream&   operator<<(std::ostream& outstream, const User &user);

#endif
