#include<set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
using namespace std;

void PrintPermutation(const vector<int>& permutation) {
    for (const auto& n : permutation) {
        cout << n << " ";
    }
    cout << endl;
}

int main() {
    int N;
    cin >> N;
    vector<int> numbers(N, 0);
    int i = 1;
    for (auto& m : numbers) {
        m = i;
        i++;
    }
    reverse(begin(numbers), end(numbers));
    PrintPermutation(numbers);
    while (prev_permutation(begin(numbers), end(numbers))) {
        PrintPermutation(numbers);
    }
}