#include<set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
        RandomIt range_begin, RandomIt range_end,
        char prefix) {
    string s;
    s.push_back(prefix);
    char p = ++prefix;
    string s1;
    s1.push_back(p);
    RandomIt itr1 = lower_bound(range_begin, range_end, s);
    RandomIt itr2 = lower_bound(range_begin, range_end, s1);
    return make_pair(itr1, itr2);
}
