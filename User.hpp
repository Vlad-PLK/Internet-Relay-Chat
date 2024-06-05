/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpolojie <vpolojie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:42:46 by vpolojie          #+#    #+#             */
/*   Updated: 2024/06/04 09:58:26 by vpolojie         ###   ########.fr       */
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
# define ALREADY_REGISTRED 5

class Command;

class SocketServer;

class User
{
private:
    std::string                 username;
    std::string                 nickname;
    std::string                 realname;
    std::string                 ip;
    int                         userfd;
    int                         admin_state;
    int                         current_state;
    std::string                 buffer;
    std::map<std::string, std::string>    _channelRights;

public:
    User(/* args */);
    User(int fd, int admin_state, int current_state);
    ~User();

    const std::string   &getUsername(void) const;
    const std::string   &getNickname(void) const;
    const std::string   &getRealname(void) const;
    const std::string   &getIp(void) const;
    int                 getFD(void) const;
    int                 getCurrentState(void) const;
    std::map<std::string, std::string>  getChannelRights(void) const;

    void                setFD(int fd);
    void                setUsername(const std::string &uname);
    void                setNickname(const std::string &nname);
    void                setRealname(const std::string &nname);
    void                setIp(const std::string &nname);
    void                setCurrentState(int state);
    void                setAdminState(int state);

    void                usr_send(const std::string &response);
    void                usr_clean(void);
    typedef void        (User::*cmdPtr)(std::vector<std::string> cmd);
    void                quit(std::vector<std::string> cmd);
    // int                process_cmd(std::string buffer);
    // void               parse_cmd(std::string &buffer);
    // int                connexion_try(void);

    bool                checkRights(std::string channelTitle, std::string channelRights); //string if multiple rihts to check at once
    bool                parseRights(std::string userRights, std::string channelRights);
    void                deleteChannelRights(std::string title);

    int                process_cmd(std::string buffer, SocketServer &server);
    void               parsing_and_handle(std::string &buffer, SocketServer &server);
};

std::ostream&   operator<<(std::ostream& outstream, const User &user);

#endif