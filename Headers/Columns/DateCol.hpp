#ifndef DATE_COLUMN_HPP
#define DATE_COLUMN_HPP

#include "Column.hpp"
#include "Date.hpp"
class DateCol : public Column
{
public:
    virtual void printAt(int index, std::ostream &os = std::cout) const override;
    virtual bool search(const std::string &value, int index) const override;

    virtual void addEntry() override;
    virtual bool removeEntry(int index) override;

    virtual bool setValue(const std::string &value, int index) override;

    virtual std::string getType() const override { return "Date"; };
    virtual std::string getValue(int index) const override;

    virtual Column *clone() const { return new DateCol(*this); };

    const Date operator[](int index) const { return column.at(index); };
    Date &operator[](int index) { return column.at(index); };

    DateCol(int size, const std::string &name) : Column(size, name), column(size) {};
    explicit DateCol(int size) : Column(size), column(size) {};
    DateCol() = default;
    ~DateCol() = default;

private:
    std::vector<Date> column;
};

#endif // DATE_COLUMN_HPP