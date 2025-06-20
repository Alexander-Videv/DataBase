#ifndef DATA_BASE_HPP
#define DATA_BASE_HPP

#include "../Tables/Table.cpp"

class DataBase
{
public:
    int size() const { return tables.size(); };

    bool createTable(const std::string &tableName);
    void removeTable(const std::string &tableName);
    void addColumn(const std::string &tableName, const std::string &columnName, const std::string &columnType);
    void addEntryInTable(const std::string &tableName);

    void insertTo(const std::string &tableName, std::string &values);
    void deleteRowsFrom(const std::string &tableName, int searchIndex, const std::string &value);

    void print(std::ostream &os = std::cout, int RPN = 0) const;
    void showTables() const;
    void printTable(const std::string &tableName, std::ostream &os = std::cout, int RPN = 0) const;
    void describe(const std::string &tableName) const;
    void select(int colIndex, const std::string &value, const std::string &tableName) const;

    void modify(const std::string &tableName, int colIndex, const std::string &newType);
    void update(const std::string &tableName, int searchIndex, const std::string &searchVal,
                int targetIndex, const std::string &targetVal);

    friend std::ostream &operator<<(std::ostream &os, const DataBase &db);
    friend std::istream &operator>>(std::istream &is, DataBase &db);

    Table &operator[](int index) { return tables.at(index); };
    const Table operator[](int index) const { return tables.at(index); };

    DataBase(const DataBase &other);
    DataBase &operator=(const DataBase &other);

    DataBase(const std::string &name) : name(name) {};
    ~DataBase() = default;

private:
    bool validateIndex(int index) const;
    int getTableIndex(const std::string &name) const;

    std::vector<Table> tables;
    std::string name;
};

#endif /// DATA_BASE_HPP