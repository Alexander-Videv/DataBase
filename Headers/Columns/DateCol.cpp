#include "DateCol.hpp"

#include "../utils/func.cpp"

void DateCol::printAt(int index, std::ostream &os) const
{
    if (index < 0 || index > column.size())
        return;
    if (nullPos.at(index))
        os << "NULL\t";
    else
        os << column.at(index) << "\t";
}

void DateCol::addEntry()
{
    Column::addEntry();
    this->column.push_back(Date());
}

bool DateCol::removeEntry(int index)
{
    if (!Column::removeEntry(index))
        return false;
    column.erase(column.begin() + index);
    return true;
}

bool DateCol::search(const std::string &value, int index) const
{
    if (index < 0 || index > column.size())
        return false;

    if (value == "NULL" && isNull(index))
        return true;

    std::stringstream parse(value);
    Date res;

    if (!(parse >> res))
        return false;

    if (column.at(index) == res)
        return true;

    return false;
}

bool DateCol::setValue(const std::string &value, int index)
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

    int day;
    int month;
    int year;

    day = stringToNumber(val.substr(0, val.find('\\')));
    val.erase(0, val.find('\\'));

    Date res(day, month, year);

    column.at(index) = res;
    setNull(index, false);
    return true;
}
std::string DateCol::getValue(int index) const
{
    if (index < 0 || index > column.size())
        throw std::invalid_argument("Bad index in getValue\n");

    std::string res;
    res += std::to_string(column[index].day) + '\\';
    res += std::to_string(column[index].month) + '\\';
    res += std::to_string(column[index].year + 1900);

    return res;
}
