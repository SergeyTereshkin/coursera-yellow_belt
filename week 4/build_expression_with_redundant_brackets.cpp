#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <deque>
using namespace std;

int main() {
    deque<string> dq;
    int x, N;
    string s;
    cin >> x;
    cin >> N;
    dq.push_back(to_string(x));
    for (int i = 0; i < N; i++) {
        string operation;
        char op;
        int number;
        cin >> op >> number;
        operation.push_back(' ');
        operation.push_back(op);
        operation += " ";
        operation += to_string(number);
        dq.push_front("(");
        dq.push_back(")");
        dq.push_back(operation);
    }
    while (!dq.empty()) {
        cout << dq[0];
        dq.pop_front();
    }
}