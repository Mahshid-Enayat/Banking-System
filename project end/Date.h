#ifndef DATE_H
#define DATE_H


class Date
{
private:
    int year;
    int month;
    int day;

public:
    Date(int _year, int _month, int _day);
    Date();

    void setYear(int _year);
    void setMonth(int _month);
    void setDay(int _day);

    int getYear() const;
    int getMonth() const;
    int getDay() const;

    ~Date();
};

#endif // DATE_H
