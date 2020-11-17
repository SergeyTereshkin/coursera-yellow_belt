#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

 using namespace std;
int main() {
    int n;
    int64_t sum = 0;
    cin >> n;
    vector<int64_t> temperatures(n);
    for (auto& t : temperatures) {
        cin >> t;
        sum += t;
    }
    int avg = sum / static_cast<int64_t>(temperatures.size());
    cout << count_if(temperatures.begin(), temperatures.end(), [avg](int64_t i){
        return i > avg;
    }) << endl;
    for (uint64_t i = 0; i < static_cast<uint64_t>(temperatures.size()); i++) {
        if (temperatures[i] > avg) {
            cout << i << " ";
        }
    }
    return 0;
}
