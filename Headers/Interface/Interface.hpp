#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "../DataBase/DataBase.hpp"
#include <iostream>

class Interface
{
public:
    bool Run();

public:
    Interface() : db(nullptr) {};
    ~Interface() { delete db; };

private:
    bool open();
    bool close();
    bool save();
    bool saveas();
    bool help();
    bool exit();

private:
    DataBase *db;
};

#endif // INTERFACE_HPP