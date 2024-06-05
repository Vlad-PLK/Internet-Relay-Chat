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
        std::vector<User> &getChannelInvited();

        void setTitle(std::string title);
        void setPassword(std::string pass);
        void setTopic(std::string message);
        void setMode(std::string new_modes);
        void setMode(char new_mode, int flag);
        void setMode(std::string new_modes, int flag);
        void setLimit(int limit);
        bool setOperators(User &user, bool flag);
        void setInvited(User &user, int flag);

        void addUser(User &user);
        void addOperator(User &user);
        void addInvited(User &user);
        void deleteUser(const std::string name);
        void deleteOperator(std::string name);
        void removeUserVector(std::vector<std::string> vector, const std::string name);
        std::string removeMode(std::string &str, char mode);
        

        void channelWelcome(User &user);
        bool userIsMember(const std::string name);
        bool userIsOperator(const std::string name);
        bool userIsBanned(const std::string name);
        bool userIsInvited(const std::string name);

        std::vector<User> &getChannelBanned();

    private:
        std::string _title;
        std::string _password;
        std::string _topic;
        std::string _modes;
        int         _limit;

        // std::vector<std::string>    _channelTopic; in case we do RPL_TOPICWHOTIME (333) : "<client> <channel> <nick> <setat>"
        std::vector<User>           _channelUsers;
        std::vector<User>           _channelOperators;
        std::vector<User>           _channelBanned;
        std::vector<User>           _channelInvited;
};

#endif