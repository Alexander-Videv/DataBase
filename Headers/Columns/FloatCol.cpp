#include "FloatCol.hpp"

void FloatCol::printAt(int index, std::ostream &os) const
{
    if (index < 0 || index > column.size())
        return;
    if (nullPos.at(index))
        os << "NULL\t";
    else
        os << column.at(index) << "\t";
}

void FloatCol::addEntry()
{
    Column::addEntry();
    this->column.push_back(0.0);
}

bool FloatCol::removeEntry(int index)
{
    if (!Column::removeEntry(index))
        return false;
    column.erase(column.begin() + index);
    return true;
}

bool FloatCol::search(const std::string &value, int index) const
{
    if (index < 0 || index > column.size())
        return false;

    if (value == "NULL" && isNull(index))
        return true;

    std::stringstream parse(value);

    float res;
    if (!(parse >> res))
        return false;

    if (column.at(index) == res)
        return true;

    return false;
}

bool FloatCol::setValue(const std::string &value, int index)
{
    if (index < 0 || index > column.size())
        return false;

    int startindex = value.find('\"') + 1;
    int endIndex = value.find('\"', startindex);

    std::string val;
    if (startindex != std::string::npos)
        val = value.substr(startindex, endIndex);
    else
        val = value;

    std::stringstream parse(val);
    float res;

    if (!(parse >> res))
    {
        setNull(index, true);
        return false;
    }

    column.at(index) = res;
    setNull(index, false);
    return true;
}

std::string FloatCol::getValue(int index) const
{
    if (index < 0 || index > column.size())
        throw std::invalid_argument("Bad index in getValue\n");
    return std::to_string(column[index]);
}
