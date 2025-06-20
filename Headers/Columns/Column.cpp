#include "Column.hpp"

Column::Column(const Column &other)
    : columnName(other.columnName),
      nullPos(other.nullPos)
{
}

Column &Column::operator=(const Column &other)
{
    if (this == &other)
        return *this;

    std::vector<bool> tempNull = other.nullPos;
    std::string tempName = other.columnName;

    this->nullPos = std::move(tempNull);
    this->columnName = std::move(other.columnName);

    return *this;
}

Column::Column(int size, const std::string &colName)
    : columnName(colName), nullPos(size)
{
    for (size_t i = 0; i < size; i++)
        nullPos[i] = true;
};

void Column::setNull(int index, bool state)
{
    if (index < 0 || index > nullPos.size())
        return;
    nullPos.at(index) = state;
}

bool Column::isNull(int index) const
{
    if (index < 0 || index > nullPos.size())
        return true;
    return nullPos.at(index);
}

bool Column::setName(const std::string &name)
{
    if (name == "")
        return false;

    try
    {
        this->columnName = name;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }

    return true;
}

void Column::addEntry()
{
    this->nullPos.push_back(true);
}

bool Column::removeEntry(int index)
{
    if (index < 0 || index > this->size())
        return false;
    nullPos.erase(nullPos.begin() + index);
    return true;
}
