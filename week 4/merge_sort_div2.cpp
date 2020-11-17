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
    auto size = (end(elements) - begin(elements));
    auto middle = begin(elements) + size/2;
    MergeSort(begin(elements), middle);
    MergeSort(middle, end(elements));
    merge(begin(elements), middle,
          middle, end(elements), range_begin);
}

