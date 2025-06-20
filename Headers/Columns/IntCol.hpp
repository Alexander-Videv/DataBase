#ifndef INTEGER_COLUMN_HPP
#define INTEGER_COLUMN_HPP

#include "Column.hpp"
class IntCol : public Column
{
public:
    virtual void printAt(int index, std::ostream &os = std::cout) const override;
    virtual bool search(const std::string &value, int index) const override;

    virtual void addEntry() override;
    virtual bool removeEntry(int index) override;

    virtual bool setValue(const std::string &value, int index) override;

    virtual std::string getType() const override { return "Int"; };
    virtual std::string getValue(int index) const override;

    virtual Column *clone() const { return new IntCol(*this); };

    const int operator[](int index) const { return column.at(index); };
    int &operator[](int index) { return column.at(index); };

    IntCol(int size, const std::string &name) : Column(size, name), column(size) {};
    explicit IntCol(int size) : Column(size), column(size) {};
    IntCol() = default;
    ~IntCol() = default;

private:
    std::vector<int> column;
};

#endif // INTEGER_COLUMN_HP