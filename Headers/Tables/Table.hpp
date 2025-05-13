#ifndef TABLE_HPP
#define TABLE_HPP

#include "../Columns/Column.hpp"
#include <string>
#include "vector"

class Table
{
private:
    std::vector<Column *> table;
    std::string name;

public:
    Table(/* args */) = default;
    ~Table() = default;
};

#endif