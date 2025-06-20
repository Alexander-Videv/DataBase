#ifndef TABLE_HPP
#define TABLE_HPP

#include "../Columns/Column.cpp"
#include <string>
#include "vector"

class Table
{
public:
    std::string getName() const { return name; };

    void search(int columnIndex, const std::string &value) const;
    void insert(std::string &values);
    void modify(int columnIndex, const std::string &newType);

    void deleteRows(int columnIndex, const std::string &searchValue);
    void deleteRowAt(int index);

    void update(int searchIndex, const std::string &searchVal,
                int targetIndex, const std::string &targetValue);

    void popEntry();
    void addEntry();
    bool addColumn(const std::string &columnName, const std::string &columnType);

    void print(std::ostream &os = std::cout, int RPN = 0) const;
    void describe(std::ostream &os = std::cout) const;

    Column *operator[](int index) { return table.at(index); };

    friend std::ostream &operator<<(std::ostream &os, const Table &table);
    friend std::istream &operator>>(std::istream &is, Table &table);

    Table(const Table &other);
    Table &operator=(const Table &other);

    Table(std::string name) : name(name), entryCount(0) {};
    ~Table() { free(); };

private:
    void printRPN(std::ostream &os, int RPN) const;
    bool validateIndex(int index) const;

    void free();

    std::vector<Column *> table;
    std::string name;
    int entryCount;
};

#endif // TABLE_HPP