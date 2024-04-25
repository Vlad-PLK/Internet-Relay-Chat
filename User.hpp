/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:42:46 by vpolojie          #+#    #+#             */
/*   Updated: 2024/04/25 09:20:08 by vpolojie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include "SocketServer.hpp"
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
    int                         userfd;
    int                         admin_state;
    int                         current_state;
    std::string                 buffer;
    std::vector<std::string>    cmds;
    std::string                 answer;

public:
    User(/* args */);
    User(int fd, int logstate);
    ~User();

    const std::string &getUsername(void) const;
    const std::string &getNickname(void) const;
    const std::string  getAnswer(void);
    int                getFD(void) const;
    void               setFD(int fd);
    void               setUsername(const std::string &uname);
    void               setNickname(const std::string &nname);
    void               setCurrentState(int state);
    void               setAdminState(int state);

    int                process_cmd(std::string buffer);
    void               parse_cmd(std::string &buffer);
};

#endif
