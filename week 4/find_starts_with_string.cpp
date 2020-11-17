#include<set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
        RandomIt range_begin, RandomIt range_end,
        const string& prefix)
{
    string s;
    s = prefix;
    s[s.size() - 1]++;
    RandomIt itr1 = lower_bound(range_begin, range_end, prefix);
    RandomIt itr2 = lower_bound(range_begin, range_end, s);
    return make_pair(itr1, itr2);
}

