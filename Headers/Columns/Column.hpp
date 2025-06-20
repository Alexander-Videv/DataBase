#ifndef COLUMN_HPP
#define COLUMN_HPP

#include <vector>
#include <iostream>
#include <sstream>
class Column
{
public:
    virtual void printAt(int index, std::ostream &os = std::cout) const = 0;
    virtual bool search(const std::string &value, int index) const = 0;
    virtual std::string getValue(int index) const = 0;
    virtual std::string getType() const = 0;
    virtual Column *clone() const = 0;
    virtual bool setValue(const std::string &value, int index) = 0;

    virtual void addEntry();
    virtual bool removeEntry(int index);

    void setNull(int index, bool state);
    bool setName(const std::string &name);

    std::string getName() const { return columnName; };
    bool isNull(int index) const;
    int size() const { return this->nullPos.size(); };

    Column(const Column &other);
    Column &operator=(const Column &other);

    explicit Column(int size, const std::string &colName = "");
    Column() = default;
    ~Column() = default;

protected:
    std::string columnName;
    std::vector<bool> nullPos;
};

#endif // COLUMN_HPP