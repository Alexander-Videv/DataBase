#include "Table.hpp"

#include <cstring>

#include "../Columns/DateCol.cpp"
#include "../Columns/FloatCol.cpp"
#include "../Columns/IntCol.cpp"
#include "../Columns/StringCol.cpp"

#include "../utils/func.cpp"

void Table::search(int columnIndex, const std::string &value) const
{
    if (!validateIndex(columnIndex))
        return;

    for (size_t i = 0; i < entryCount; i++)
    {
        if (table.at(columnIndex)->search(value, i))
        {
            for (size_t j = 0; j < table.size(); j++)
            {
                table[j]->printAt(i);
            }
            std::cout << "\n";
        }
    }
}

void Table::insert(std::string &values)
{
    this->addEntry();
    std::string currValue;
    for (size_t i = 0; i < table.size(); i++)
    {
        currValue = getValue(values);

        if (!table[i]->setValue(currValue, entryCount - 1))
        {
            std::cout << "Invalid index or value!\n";
            popEntry();
            return;
        }
    }
}

void Table::modify(int columnIndex, const std::string &newType)
{
    if (!validateIndex(columnIndex))
        return;

    if (!this->addColumn(table[columnIndex]->getName(), newType))
        return;

    int failed = 0;
    std::vector<int> failedIndices;

    for (size_t i = 0; i < entryCount; i++)
    {
        try
        {
            if (!this->table[table.size() - 1]->setValue(table[columnIndex]->getValue(i), i))
            {
                failedIndices.push_back(i);
                failed++;
            }
            else if (this->table[columnIndex]->isNull(i))
            {
                this->table[table.size() - 1]->setNull(i, true);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    std::swap(this->table[table.size() - 1], table[columnIndex]);

    delete table[table.size() - 1];
    table.pop_back();

    std::cout << "Out of " << entryCount << " entries " << failed << " failed, while " << entryCount - failed << " succeeded.\n";
    if (failed)
    {
        std::cout << "Failed indices are : ";
        for (size_t i = 0; i < failed; i++)
        {
            std::cout << i;
            if (i < failed - 1)
                std::cout << ", ";
        }
        std::cout << "\n";
    }
}

void Table::deleteRows(int columnIndex, const std::string &searchValue)
{
    if (!validateIndex(columnIndex))
        return;

    for (size_t i = 0; i < entryCount; i++)
    {
        if (table[columnIndex]->search(searchValue, i))
            deleteRowAt(i);
    }
}

void Table::deleteRowAt(int index)
{
    if (index < 0 || index > entryCount)
        return;
    for (size_t i = 0; i < table.size(); i++)
    {
        table[i]->removeEntry(index);
    }

    entryCount--;
}

void Table::update(int searchIndex, const std::string &searchVal, int targetIndex, const std::string &targetValue)
{
    if (!validateIndex(searchIndex) || !validateIndex(targetIndex))
        return;

    for (size_t i = 0; i < entryCount; i++)
    {
        if (table.at(searchIndex)->search(searchVal, i))
        {
            if (targetValue == "NULL")
                table[targetIndex]->setNull(i, true);
            else if (!table[targetIndex]->setValue(targetValue, i))
            {
                std::cout << "Invalid target index or target value!\n";
            }
        }
    }
}

void Table::addEntry()
{
    entryCount++;
    for (size_t i = 0; i < table.size(); i++)
        table[i]->addEntry();
}

void Table::popEntry()
{
    for (size_t i = 0; i < table.size(); i++)
        table[i]->removeEntry(table[i]->size());
}

bool Table::addColumn(const std::string &columnNane, const std::string &columnType)
{
    std::string lowerType = toLowerStr(columnType);

    try
    {
        if (lowerType == "int")
            this->table.push_back(new IntCol(entryCount, columnNane));
        else if (lowerType == "date")
            this->table.push_back(new DateCol(entryCount, columnNane));
        else if (lowerType == "float")
            this->table.push_back(new FloatCol(entryCount, columnNane));
        else if (lowerType == "string")
            this->table.push_back(new StringCol(entryCount, columnNane));
        else
        {
            std::cout << "Invalid column type!\n";
            return false;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }

    return true;
}

void Table::print(std::ostream &os, int RPN) const
{
    os << name << "\n"
       << entryCount << " " << this->table.size() << "\n";

    this->describe(os);
    if (RPN == 0)
    {
        for (size_t i = 0; i < entryCount; i++)
        {
            for (size_t j = 0; j < table.size(); j++)
            {
                table[j]->printAt(i, os);
            }
            os << "\n";
        }
    }
    else
    {
        printRPN(os, RPN);
    }
}

void Table::describe(std::ostream &os) const
{
    for (size_t i = 0; i < table.size(); i++)
        os << table[i]->getType() << "\t";

    os << "\n";

    for (size_t i = 0; i < table.size(); i++)
        os << table[i]->getName() << "\t";

    os << "\n";
}

Table::Table(const Table &other)
    : name(other.name),
      entryCount(other.entryCount)
{
    for (size_t i = 0; i < other.table.size(); i++)
    {
        this->table.push_back(other.table[i]->clone());
    }
}

Table &Table::operator=(const Table &other)
{
    if (this == &other)
        return *this;

    Table buff(other);

    this->table = std::move(buff.table);
    this->name = std::move(buff.name);
    this->entryCount = other.entryCount;

    return *this;
}

void Table::printRPN(std::ostream &os, int RPN) const
{
    std::string RPNcommand;
    int currCount = 0;
    int maxPage = 0;
    if (entryCount % RPN == 0)
    {
        maxPage = ((entryCount / RPN) - 1) * RPN;
    }
    else
    {
        maxPage = (entryCount / RPN) * RPN;
    }
    while (true)
    {
        int currMax = std::min(currCount + RPN, entryCount);
        for (size_t i = currCount; i < currMax; i++)
        {
            for (size_t j = 0; j < table.size(); j++)
            {
                table[j]->printAt(i, os);
            }
            os << "\n";
        }
        std::cout << "Enter a command : first,next,previous,last,exit.\n";
        std::cin >> RPNcommand;
        if (RPNcommand == "first")
        {
            currCount = 0;
        }
        else if (RPNcommand == "next")
        {
            currCount = std::min(currCount + RPN, maxPage);
        }
        else if (RPNcommand == "previous")
        {
            currCount - std::max(currCount - RPN, 0);
        }
        else if (RPNcommand == "last")
        {
            currCount = maxPage;
        }
        else if (RPNcommand == "exit")
        {
            break;
        }
        else
            std::cout << "Command not supported.\n";
    }

    std::cin.ignore();
}

bool Table::validateIndex(int index) const
{
    if (index < 0 || index > table.size() - 1)
    {
        std::cout << "Invalid column index!\n";
        return false;
    }
    return true;
}

void Table::free()
{
    for (size_t i = 0; i < table.size(); i++)
    {
        delete table[i];
    }
}

std::ostream &operator<<(std::ostream &os, const Table &table)
{
    table.print(os);
    return os;
}

std::istream &operator>>(std::istream &is, Table &table)
{
    Table temp("");

    int rowSize;
    int colSize;

    is >> temp.name >> rowSize >> colSize;
    is.ignore();

    std::string line;
    std::string line2;
    std::getline(is, line);
    std::getline(is, line2);

    std::string currType;
    std::string currName;
    for (size_t i = 0; i < colSize; i++)
    {
        currType = getNextTokenTable(line);
        currName = getNextTokenTable(line2);
        if (!temp.addColumn(currName, currType))
        {
            is.setstate(std::ios::failbit);
            return is;
        }
    }

    std::string cellValue;

    for (size_t i = 0; i < rowSize; i++)
    {
        std::getline(is, line);
        temp.addEntry();
        for (size_t j = 0; j < temp.table.size(); j++)
        {
            cellValue = getValueTable(line);
            if (cellValue == "NULL")
                continue;

            if (!temp[j]->setValue(cellValue, i))
            {
                std::cout << "Invalid index or value!\n";
                is.setstate(std::ios::failbit);
                return is;
            }
        }
    }

    table = temp;

    return is;
}
