#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};


void TestIfNumZero() {
    Rational rational = {0, 5};
    AssertEqual(rational.Denominator(), 1);
}

void ReduceFraction() {
    Rational rational1 = {5, 10};
    Assert(rational1.Numerator() == 1 && rational1.Denominator() == 2,
           "Reduce fraction");
}

void NegativeFraction() {
    Rational rational2 = {1, -5};
    Assert(rational2.Numerator() == -1 && rational2.Denominator() == 5,
            "Negative denominator");
    Rational rational3 = {-1, 5};
    Assert(rational2.Numerator() == -1 && rational2.Denominator() == 5,
          "Negative numerator");
}


void Default() {
    Rational rational;
    Assert(rational.Numerator() == 0 && rational.Denominator() == 1,
            "Default creation");
}

void PositiveFraction() {
    Rational rational = {-2, -3};
    Assert(rational.Numerator() == 2 && rational.Denominator() == 3,
           "negative num and denum");
    Rational rational1 = {2, 3};
    Assert(rational.Numerator() == 2 && rational.Denominator() == 3,
           "positive num and denum");
}

int main() {
    TestRunner runner;
    runner.RunTest(TestIfNumZero, "TestIfNumZero");
    runner.RunTest(ReduceFraction, "ReduceFraction");
    runner.RunTest(NegativeFraction, "NegativeFraction");
    runner.RunTest(Default, "Default");
    runner.RunTest(PositiveFraction, "PositiveFraction");
    return 0;
}
