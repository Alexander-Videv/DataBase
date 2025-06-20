#ifndef FLOAT_COLUMN_HPP
#define FLOAT_COLUMN_HPP

#include "Column.hpp"
class FloatCol : public Column
{
public:
    virtual void addEntry() override;
    virtual bool removeEntry(int index) override;

    virtual void printAt(int index, std::ostream &os = std::cout) const override;
    virtual bool search(const std::string &value, int index) const override;

    virtual bool setValue(const std::string &value, int index) override;

    virtual std::string getType() const override { return "Float"; };
    virtual std::string getValue(int index) const override;

    virtual Column *clone() const { return new FloatCol(*this); };

    const float operator[](int index) const { return column.at(index); };
    float &operator[](int index) { return column.at(index); };

    FloatCol(int size, const std::string &name) : Column(size, name), column(size) {};
    explicit FloatCol(int size) : Column(size), column(size) {};
    FloatCol() = default;
    ~FloatCol() = default;

private:
    std::vector<float> column;
};

#endif // FLOAT_COLUMN_HPP