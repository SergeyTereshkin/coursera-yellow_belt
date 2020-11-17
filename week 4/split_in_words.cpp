#include<set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
using namespace std;

vector<string> SplitIntoWords(const string& s) {
    vector<string> words;
    auto itr = find(begin(s), end(s), ' ');
    words.push_back({begin(s), itr});
    while (itr < s.end()) {
        auto last_itr = itr;
        itr = find(++last_itr, end(s), ' ');
        string word = {last_itr, itr};
        words.push_back(word);
    }
    return words;
}

