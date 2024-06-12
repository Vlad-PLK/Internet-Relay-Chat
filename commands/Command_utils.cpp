#include "../Command.hpp"

std::vector<std::string>    splitSetter(std::string param)
{
    std::vector<std::string> res;
    std::stringstream ss(param);
    std::string copy;
    while (std::getline(ss, copy, ','))
        res.push_back(copy);
    return res;
}