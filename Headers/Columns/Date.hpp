
#include <cstdint>

struct Date
{
    uint16_t day : 5;
    uint16_t month : 4;
    uint16_t year : 7;

    bool operator==(const Date &other) const;
    bool operator!=(const Date &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Date &date);
    friend std::istream &operator>>(std::istream &is, Date &date);

    Date() : day(1), month(1), year(0) {};
    Date(int d, int m, int y) : day(day), month(m), year(y) {};
};

std::ostream &operator<<(std::ostream &os, const Date &date)
{
    os << date.day << "\\" << date.month << "\\" << date.year + 1900;
    return os;
}

inline std::istream &operator>>(std::istream &is, Date &date)
{
    int day;
    int month;
    int year;
    char buff;

    is >> day;
    is >> buff;
    if (buff != '\\')
    {
        is.setstate(std::ios::failbit);
        return is;
    }

    is >> month;
    is >> buff;
    if (buff != '\\')
    {
        is.setstate(std::ios::failbit);
        return is;
    }

    is >> year;

    date.day = day;
    date.month = month;
    date.year = year - 1900;

    return is;
}

bool Date::operator==(const Date &other) const
{
    return this->day == other.day && this->month == other.month && this->year == other.year;
}

inline bool Date::operator!=(const Date &other) const
{
    return !(*this == other);
}
