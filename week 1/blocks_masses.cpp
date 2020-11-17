#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

 using namespace std;
int main() {
    uint64_t number;
    uint16_t density;
    cin >> number >> density;
    uint64_t mass = 0;
    for (uint64_t i = 0; i < number; i++) {
        uint64_t width, height, depth;
        cin >> width >> height >> depth;
        mass += width * height * depth * density;
    }
    cout << mass;
    return 0;
}