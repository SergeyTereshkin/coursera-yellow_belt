#include "phone_number.h"
#include <sstream>
#include <iostream>

PhoneNumber::PhoneNumber(const string &international_number) {
    stringstream ss;
    bool is = true;
    ss << international_number;
    string country_code, city_code, local_number;
    if (ss.peek() == '+') {
        ss.ignore(1);
        getline(ss, country_code, '-');
    }
    else {
        is = false;
    }
    if (!ss.eof()) {
        getline(ss, city_code, '-');
    }
    else {
        is = false;
    }
    if (!ss.eof()) {
        ss >> local_number;
    }
    else {
        is = false;
    }
    if (is && !country_code.empty() && !city_code.empty() && !local_number.empty()) {
        PhoneNumber::country_code_ = country_code;
        PhoneNumber::city_code_ = city_code;
        PhoneNumber::local_number_ = local_number;
    }
    else {
        throw invalid_argument(international_number);
    }
}
string PhoneNumber::GetCityCode() const {
    return PhoneNumber::city_code_;
}
string PhoneNumber::GetCountryCode() const {
    return PhoneNumber::country_code_;
}
string PhoneNumber::GetLocalNumber() const {
    return PhoneNumber::local_number_;
}
string PhoneNumber::GetInternationalNumber() const {
    string country_code = GetCountryCode();
    string city_code = GetCityCode();
    string local_number = GetLocalNumber();
    string international_number = "+" + country_code + "-" + city_code
            + "-" + local_number;
    return international_number;
}
