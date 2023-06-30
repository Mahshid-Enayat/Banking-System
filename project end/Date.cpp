#include "Date.h"

Date::Date(int _year, int _month, int _day)
{
    year = _year;
    month = _month;
    day = _day;
    return;
}

Date::Date()
{
    return;
}

void Date::setYear(int _year)
{
    year = _year;
    return;
}

void Date::setMonth(int _month)
{
    month = _month;
    return;
}

void Date::setDay(int _day)
{
    day = _day;
    return;
}

int Date::getYear() const
{
    return this->year;
}

int Date::getMonth() const
{
    return this->month;
}

int Date::getDay() const
{
    return this->day;
}

Date::~Date()
{
    return;
}
