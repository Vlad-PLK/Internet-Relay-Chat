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

// Need to check if user is an operator !!
void Channel::setMode(std::string new_modes, int flag) // flag == 0 means remove and flag == 1 means add
{

    int i = 0;
    while (new_modes[++i])
    {
        if (!flag)
        {
            if (this->_modes.find(new_modes[i]))
                this->setMode(removeMode(this->_modes, new_modes[i]));
            // else
                // ERROR MESSAGE (?) the mode to delete is not preset
        }
        else
        {
            if (!this->_modes.find(new_modes[i]))
                this->setMode(this->_modes + new_modes[i]);
            // else
                // ERROR MESSAGE (?) the mode to add exists already
        }
    }
}