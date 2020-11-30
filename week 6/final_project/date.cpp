#include "date.h"
#include <iomanip>
#include <vector>

using namespace std;

Date :: Date() {
    year = 0;
    month = 0;
    day = 0;
}
Date :: Date(int new_year, int new_month, int new_day) {
    year = new_year;
    month = new_month;
    day = new_day;
}
int Date ::GetYear() const {
    return year;
}
int Date ::GetMonth() const {
    return month;
}
int Date ::GetDay() const {
    return day;
}

Date ParseDate(istream& is) {
    stringstream ss1;
    string date;
    is >> date;
    ss1 << date;
    int day, month, year;
    char c1, c2;
    ss1 >> year >> c1 >> month >> c2 >> day;
    return {year, month, day};
}


ostream& operator<<(ostream& os, const Date& date) {
    os << setw(4) << setfill('0') << date.GetYear() << '-'
         << setw(2) << setfill('0') << date.GetMonth() << '-'
         << setw(2) << setfill('0') << date.GetDay();
    return os;
}

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() < rhs.GetYear()) {
        return true;
    }
    if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() < rhs.GetMonth()) {
        return true;
    }
    return lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() < rhs.GetDay();
};
