#ifndef STRING_COLUMN_HPP
#define STRING_COLUMN_HPP

#include "Column.hpp"

class StringCol : public Column
{
public:
    virtual void printAt(int index, std::ostream &os = std::cout) const override;

    virtual void addEntry() override;
    virtual bool removeEntry(int index) override;

    virtual std::string getType() const override { return "String"; };

    virtual Column *clone() const { return new StringCol(*this); };

    virtual bool search(const std::string &value, int index) const override;

    virtual bool setValue(const std::string &value, int index) override;
    virtual std::string getValue(int index) const override;

    const std::string operator[](int index) const { return column.at(index); };
    std::string &operator[](int index) { return column.at(index); };

    StringCol(int size, const std::string &name) : Column(size, name), column(size) {};
    explicit StringCol(int size) : Column(size), column(size) {};
    StringCol() = default;
    ~StringCol() = default;

private:
    std::vector<std::string> column;
};

#endif // STRING_COLUMN_HPP