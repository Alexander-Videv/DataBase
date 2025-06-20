#include "StringCol.hpp"
#include "../utils/func.cpp"

void StringCol::printAt(int index, std::ostream &os) const
{
    if (index < 0 || index > column.size())
        return;
    if (nullPos.at(index))
        os << "NULL\t";
    else
        os << column.at(index) << "\t";
}

void StringCol::addEntry()
{
    Column::addEntry();
    this->column.push_back(std::string());
}

bool StringCol::removeEntry(int index)
{
    if (!Column::removeEntry(index))
        return false;
    column.erase(column.begin() + index);
    return true;
}

bool StringCol::search(const std::string &value, int index) const
{
    if (index < 0 || index > column.size())
        return false;

    std::string lower = toLowerStr(column[index]);

    if (value == "NULL" && nullPos.at(index))
        return true;
    if (lower.find(toLowerStr(value)) != std::string::npos)
        return true;

    return false;
}

bool StringCol::setValue(const std::string &value, int index)
{

    if (index < 0 || index > column.size())
        return false;

    std::string val;

    if (value.find('\"') == std::string::npos)
        val = '\"' + value + '\"';
    else
        val = value;

    try
    {
        column.at(index) = val;
        setNull(index, false);
    }
    catch (const std::exception &e)
    {
        this->nullPos.at(index) = true;
        return false;
    }

    return true;
}

std::string StringCol::getValue(int index) const
{
    if (index < 0 || index > column.size())
        throw std::invalid_argument("Bad index in getValue\n");

    return column[index];
}
