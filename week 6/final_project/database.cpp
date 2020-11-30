#include "database.h"
#include "date.h"
#include <iostream>

using namespace std;

Database::Database() {
    //events[{}] = {""};
    //vec_events[{}] = {""};
};

void Database::Add(const Date &date, const string &event) {
    auto p = events[date].insert(event);
    if (p.second) {
        vec_events[date].push_back(event);
    }
};


pair<Date, string> Database::Last(Date date) const {
    auto itr = vec_events.upper_bound(date);
    if (itr == begin(vec_events)) {
        throw invalid_argument("This is the smallest data");
    }
    auto new_itr = --itr;
    auto data = make_pair(new_itr->first, new_itr->second.back());
    return data;
}

int Database::RemoveIf(const std::function<bool(const Date&, const string&)>& predicate) {
    auto set_itr = events.begin();
    while (set_itr != events.end()) {
        const Date &date = set_itr->first;
        for (auto elem = set_itr->second.begin(); elem != set_itr->second.end();) {
            if (predicate(date, *elem)) {
                set_itr->second.erase(elem++);
            }
            else {
                ++elem;
            }
        }
        if (set_itr->second.empty()) {
            events.erase(set_itr++);
        } else {
            ++set_itr;
        }
    }
    int removed = 0;
    auto itr = vec_events.begin();
    while(itr != vec_events.end()){
        removed += itr->second.size();
        const Date &date = itr->first;
        auto partition = stable_partition(itr->second.begin(),itr->second.end(),
                [predicate,date](const string& str){
            return !predicate(date,str);
        });
        itr->second.erase(partition,itr->second.end());
        removed -= itr->second.size();
        if (itr->second.empty()) {
            vec_events.erase(itr++);
        } else {
            ++itr;
        }
    }

    return removed;
}


vector<pair<const Date*, const string*>> Database::FindIf(const std::function<bool(const Date&, const string&)>& predicate) const {
    vector<pair<const Date*, const string*>> res;
    for(auto i = begin(vec_events); i != end(vec_events); i++) {
        const Date& date = i->first;
        auto itr = find_if(i->second.begin(),i->second.end(),[&date, &res, predicate](const string &str) {
            if(predicate(date, str)){
                res.push_back(make_pair(&date, &str));
            }
            return false;
        });
    }
    return res;
}

void Database::Print(ostream &os) const {
    if (events.empty()) {
        return;
    }
    for (auto& m : vec_events) {
        int cur_year = m.first.GetYear();
        int cur_month = m.first.GetMonth();
        int cur_day = m.first.GetDay();
        vector<string> ev;
        ev = m.second;
        vector<string> ::iterator itr;
        for (itr = ev.begin(); itr != ev.end(); ++itr) {
            os << setw(4) << setfill('0') << cur_year << '-'
                 << setw(2) << setfill('0') << cur_month << '-'
                 << setw(2) << setfill('0') << cur_day << " ";
            os << *itr << endl;
        }
    }
}

ostream& operator<<(ostream& os, const pair<Date, string>& p) {
    int year = p.first.GetYear();
    int month = p.first.GetMonth();
    int day = p.first.GetDay();
    os << setw(4) << setfill('0') << year << '-'
         << setw(2) << setfill('0') << month << '-'
         << setw(2) << setfill('0') << day << " ";
    os << p.second;
    return os;
}

ostream& operator<<(ostream& os, const pair<const Date*, const string*>& p) {
    int year = p.first->GetYear();
    int month = p.first->GetMonth();
    int day = p.first->GetDay();
    os << setw(4) << setfill('0') << year << '-'
       << setw(2) << setfill('0') << month << '-'
       << setw(2) << setfill('0') << day << " ";
    os << *p.second;
    return os;
}

bool operator==(const Date& lhs, const Date& rhs) {
    return (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() == rhs.GetDay());
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}

ostream& operator<<(ostream& os, const pair<Date, vector<string>>& p) {
    int year = p.first.GetYear();
    int month = p.first.GetMonth();
    int day = p.first.GetDay();
    vector<string> vec = p.second;
    for (const auto &v : vec) {
        os << setw(4) << setfill('0') << year << '-'
           << setw(2) << setfill('0') << month << '-'
           << setw(2) << setfill('0') << day << " ";
        os << v;
    }
    return os;
}

ostream& operator<<(ostream& os, const vector<string>& vec) {
    for (const auto &v : vec) {
        os << v << " ";
    }
    return os;
}
