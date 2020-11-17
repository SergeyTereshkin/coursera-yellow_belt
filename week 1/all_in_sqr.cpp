#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <utility>
#include <map>

using namespace std;

template<typename T> T Sqr(T x);
template<typename First, typename Second> pair<First, Second> operator*(
        pair<First, Second> p1, pair<First, Second> p2);
template<typename First, typename Second> map<First, Second> operator*(
        map<First, Second> m1, map<First, Second> m2);
template <typename T> vector<T> operator*(vector<T> v1, vector<T> v2);


template <typename T>
T Sqr(T x) {
    return x * x;
}


template<typename First, typename Second> pair<First, Second> operator*(
        pair<First, Second> p1, pair<First, Second> p2) {
    First p3 = p1.first * p2.first;
    Second p4 = p1.second * p2.second;
    return make_pair(p3, p4);
}


template<typename First, typename Second> map<First, Second> operator*(
        map<First, Second> m1, map<First, Second> m2) {
    vector<Second> seconds1;
    vector<Second> seconds2;
    vector<First> firsts1;
    map<First, Second> new_map;
    for (const auto& m : m1) {
        seconds1.push_back(m.second);
        firsts1.push_back(m.first);
    }
    for (const auto& m : m2) {
        seconds2.push_back(m.second);
    }
    for (size_t i = 0; i < firsts1.size(); i++) {
        new_map[firsts1[i]] = seconds1[i] * seconds2[i];
    }
    return new_map;
}

template <typename T> vector<T> operator*(vector<T> v1, vector<T> v2) {
    vector<T> new_vector;
    for (size_t i = 0; i < v1.size(); i++) {
        new_vector.push_back(v1[i] * v2[i]);
    }
    return new_vector;
}
int main() {
    // Пример вызова функции
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
            {4, {2, 2}},
            {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
}