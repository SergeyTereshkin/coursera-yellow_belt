#pragma once
#include <memory>
#include <sstream>

class Date {
public:
    Date();
    Date(int new_year, int new_month, int new_day);
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
private:
    int year;
    int month;
    int day;
};

std::ostream& operator<<(std::ostream& os, const Date& date);

Date ParseDate(std::istream& is);


bool operator<(const Date& lhs, const Date& rhs);


