#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "User.hpp"
#include "SocketServer.hpp"

class User;

class Channel
{
    public:
        Channel(void);
        ~Channel(void);

        std::string getTitle() const;
        std::string &getPassword();
        std::string getTopic() const;
        std::string getMode() const;
        int         getLimit() const;
        std::vector<User> &getChannelUsers();
        std::vector<User> &getChannelOperators();

        void setTitle(User &user, std::string title);
        void setPassword(User &user, std::string pass);
        void setTopic(User &user, std::string message);
        // void setMode(User &user, char new_mode);
        void setLimit(User &user, int limit);

        void addUser(const User &user);

    private:
        std::string _title;
        std::string _password;
        std::string _topic;
        std::string _mode;
        int         _limit;

        std::vector<User> _channelUsers;
        std::vector<User> _channelOperators;
};

#endif