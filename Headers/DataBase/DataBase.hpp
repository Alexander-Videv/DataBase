#ifndef DATA_BASE_HPP
#define DATA_BASE_HPP

#include "../Tables/Table.hpp"

class DataBase
{
private:
    std::vector<Table> db;
    std::string name;

public:
    DataBase() = default;
    ~DataBase() = default;
};

#endif /// DATA_BASE_HPP