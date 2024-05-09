#include "User.hpp"

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
        std::string getLimit() const;
        std::vector<User> &getChannelUsers();
        std::vector<User> &getChannelOperators();

        void setTitle(std::string title);
        void setPassword(std::string pass);
        void setTopic(std::string message);
        // void setMode(char new_mode);
        void setLimit(int limit);

        void addUser(User user);

    private:
        std::string _title;
        std::string _password;
        std::string _topic;
        std::string _mode;
        std::string _limit;

        std::vector<User> _channelUsers;
        std::vector<User> _channelOperators;
};