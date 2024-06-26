#include "SocketServer.hpp"

std::string Channel::removeMode(std::string &str, char mode)
{
    std::string result;
    for (std::string::size_type i = 0; i < str.size(); ++i)
    {
        if (str[i] != mode)
            result += str[i];
    }
    return (result);
}

void Channel::setMode(char new_mode, int flag) // flag == 0 means remove and flag == 1 means add
{
    if (!flag)
    {
        if (this->_modes.find(new_mode) != std::string::npos)
            this->setMode(removeMode(this->_modes, new_mode));
    }
    else
    {
        if (this->_modes.find(new_mode) == std::string::npos)
            this->setMode(this->_modes + new_mode);
    }
}