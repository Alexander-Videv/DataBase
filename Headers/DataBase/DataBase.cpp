#include "DataBase.hpp"

bool DataBase::createTable(const std::string &tableName)
{
    try
    {
        tables.push_back(Table(tableName));
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }

    return true;
}

void DataBase::removeTable(const std::string &tableName)
{
    int index = getTableIndex(tableName);
    if (!validateIndex(index))
        return;

    tables.erase(tables.begin() + index);
}

void DataBase::addColumn(const std::string &tableName, const std::string &columnName, const std::string &columnType)
{
    int index = getTableIndex(tableName);
    if (!validateIndex(index))
        return;

    tables[index].addColumn(columnName, columnType);
}

void DataBase::addEntryInTable(const std::string &tableName)
{
    int index = getTableIndex(tableName);
    if (!validateIndex(index))
        return;

    tables[index].addEntry();
}
void DataBase::insertTo(const std::string &tableName, std::string &values)
{
    int index = getTableIndex(tableName);
    if (!validateIndex(index))
        return;

    tables[index].insert(values);
}
void DataBase::deleteRowsFrom(const std::string &tableName, int searchIndex, const std::string &value)
{
    int index = getTableIndex(tableName);
    if (!validateIndex(index))
        return;

    tables[index].deleteRows(searchIndex, value);
};

void DataBase::print(std::ostream &os, int RPN) const
{
    os << this->name << "\n";
    os << this->size() << "\n";
    for (size_t i = 0; i < tables.size(); i++)
    {
        tables[i].print(os, RPN);
        // os << "end\n";
    }
}

void DataBase::showTables() const
{
    for (size_t i = 0; i < tables.size(); i++)
    {
        std::cout << i + 1 << ")" << tables[i].getName() << "\n";
    }
}

void DataBase::printTable(const std::string &tableName, std::ostream &os, int RPN) const
{
    int index = getTableIndex(tableName);
    if (!validateIndex(index))
        return;

    tables[index].print(os, RPN);
}

void DataBase::describe(const std::string &tableName) const
{
    int index = getTableIndex(tableName);
    if (!validateIndex(index))
        return;

    tables[index].describe();
}

void DataBase::select(int colIndex, const std::string &value, const std::string &tableName) const
{
    int index = getTableIndex(tableName);
    if (!validateIndex(index))
        return;

    tables[index].search(colIndex, value);
}

void DataBase::modify(const std::string &tableName, int colIndex, const std::string &newType)
{
    int index = getTableIndex(tableName);
    if (!validateIndex(index))
        return;

    tables[index].modify(colIndex, newType);
}

void DataBase::update(const std::string &tableName, int searchIndex, const std::string &searchVal,
                      int targetIndex, const std::string &targetVal)
{
    int index = getTableIndex(tableName);
    if (!validateIndex(index))
        return;

    tables[index].update(searchIndex, searchVal, targetIndex, targetVal);
}

int DataBase::getTableIndex(const std::string &name) const
{
    for (size_t i = 0; i < tables.size(); i++)
    {
        if (tables[i].getName() == name)
            return i;
    }

    std::cout << "No table found with name - " << name << "\n";

    return -1;
}

DataBase::DataBase(const DataBase &other)
    : tables(other.tables),
      name(other.name)
{
}

DataBase &DataBase::operator=(const DataBase &other)
{
    if (this == &other)
        return *this;

    DataBase buff(other);

    this->tables = std::move(buff.tables);
    this->name = std::move(buff.name);

    return *this;
}

bool DataBase::validateIndex(int index) const
{
    if (index < 0 || index > tables.size())
        return false;
    return true;
}

std::ostream &operator<<(std::ostream &os, const DataBase &db)
{
    db.print(os);
    return os;
}

std::istream &operator>>(std::istream &is, DataBase &db)
{
    int size;

    DataBase temp(db.name);

    is >> temp.name;
    is >> size;
    Table buff("");

    for (size_t i = 0; i < size; i++)
    {
        if (!(is >> buff))
            return is;
        temp.tables.push_back(buff);
    }

    db = temp;

    return is;
}
