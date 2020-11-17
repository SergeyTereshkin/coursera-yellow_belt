#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <utility>
#include <map>

using namespace std;

template<typename First, typename Second, typename T> Second& GetRefStrict(map<First, Second>& init_map, const T& key);

template<typename First, typename Second, typename T> Second& GetRefStrict(map<First, Second>& init_map, const T& key) {
    Second value;
    if (init_map.count(key) == 0) {
        throw runtime_error("");
    }
    return init_map[key];
}
