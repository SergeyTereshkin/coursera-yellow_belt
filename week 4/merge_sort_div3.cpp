#include<set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if (range_end - range_begin < 2) {
        return;
    }
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    vector<typename RandomIt::value_type> temp;
    auto size = (end(elements) - begin(elements));
    auto fthird = begin(elements) + size/3;
    auto sthird = fthird + size/3;
    MergeSort(begin(elements), fthird);
    MergeSort(fthird, sthird);
    MergeSort(sthird, end(elements));
    merge(begin(elements), fthird,
          fthird, sthird, back_inserter(temp));
    merge(begin(temp), end(temp), sthird, end(elements), range_begin);
}
