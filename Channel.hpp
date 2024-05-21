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
        std::string getModes() const;
        int         getLimit() const;
        std::vector<User> &getChannelUsers();
        std::vector<User> &getChannelOperators();

        void setTitle(std::string title);
        void setPassword(std::string pass);
        void setTopic(std::string message);
        void setMode(std::string new_mode);
        void setMode(std::string new_modes, int flag);
        void setLimit(int limit);
        void setOperators(User &user, int flag);

        void addUser(User &user);
        void addOperator(User &user);
        void deleteUser(std::string name);
        void deleteOperator(std::string name);
        std::string removeMode(std::string &str, char mode);

        //void channelWelcome(User &user);
        bool userIsMember(std::string name);
        bool userIsOperator(std::string name);
        bool userIsBanned(std::string name);

        std::vector<User> &getChannelBanned();

    private:
        std::string _title;
        std::string _password;
        std::string _topic;
        std::string _modes;
        int         _limit;

        std::vector<User> _channelUsers;
        std::vector<User> _channelOperators;
        std::vector<User> _channelBanned;
};

#endif