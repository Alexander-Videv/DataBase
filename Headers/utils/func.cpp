
#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

std::string toLowerStr(const std::string &str)
{
    std::string res = str;
    for (size_t i = 0; i < str.size(); i++)
        res[i] = tolower(res[i]);

    return res;
}

std::string getNextToken(std::string &str)
{
    std::string res = str.substr(0, str.find(' '));
    str.erase(0, res.size() + 1);
    return res;
}

std::string getNextTokenTable(std::string &str)
{
    std::string res = str.substr(0, str.find('\t'));
    str.erase(0, res.size() + 1);
    return res;
}

int getIndex(std::string &line)
{
    std::string indStr = getNextToken(line);
    return std::strtol(indStr.c_str(), nullptr, 10) - 1;
}

std::string getValue(std::string &str)
{
    std::string value;
    if (str.find('\"') != std::string::npos && str.find('\"') < str.find(' '))
    {
        int startindex = str.find('\"');
        int endIndex = str.find('\"', startindex + 1) + 1;
        while (str[endIndex - 2] == '\\')
        {
            endIndex = str.find('\"', endIndex) + 1;
        }
        value = str.substr(startindex, endIndex);
        str.erase(0, endIndex + 1);
    }
    else
    {
        value = getNextToken(str);
    }

    return value;
}

std::string getValueTable(std::string &str)
{
    std::string value;
    if (str.find('\"') != std::string::npos && str.find('\"') < str.find(' '))
    {
        int startindex = str.find('\"');
        int endIndex = str.find('\"', startindex + 1) + 1;
        while (str[endIndex - 2] == '\\')
        {
            endIndex = str.find('\"', endIndex) + 1;
        }
        value = str.substr(startindex, endIndex);
        str.erase(0, endIndex + 1);
    }
    else
    {
        value = getNextTokenTable(str);
    }

    return value;
}

int stringToNumber(const std::string &str)
{
    int res = 0;

    int count = str.length();

    for (int i = 0; i < count; i++)
    {
        res *= 10;
        res += str.at(i) - '0';
    }

    return res;
}

#endif