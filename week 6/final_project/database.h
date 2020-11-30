#pragma once
#include "date.h"
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;
class Database {
public:
    Database();
    void Add(const Date& date, const string& event);


    int RemoveIf(const function<bool(const Date&, const string&)>& predicate);

    vector<pair<const Date*, const string*>> FindIf(const function<bool(const Date&, const string&)>& predicate) const;

    pair<Date, string> Last(Date date) const;

    void Print(ostream& os) const;
private:
    map<Date, set<string>> events;
    map<Date, vector<string>> vec_events;
};

ostream& operator<<(ostream& os, const pair<Date, vector<string>>& p);

ostream& operator<<(ostream& os, const pair<const Date*, const string*>& p);

ostream& operator<<(ostream& os, const pair<Date, string>& p);

bool operator==(const Date& lhs, const Date& rhs);

ostream& operator<<(ostream& os, const vector<string>& vec);