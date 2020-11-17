#include<set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border){
    vector<T> greater_elements;
    for (const auto& m : elements) {
        if (m > border) {
            greater_elements.push_back(m);
        }
    }
    return greater_elements;
}

