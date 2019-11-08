#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include <bits/stdc++.h>
#include <string>
using namespace std;

string IntToString(int x) {
    // TODO - you fill in here.
    long int z = x;
    if (z == 0){
        return "0";
    }

    string s = "";
    bool sign = z < 0;
    if(sign){
        z = -z;
    }
    while (z > 0) {
        s.push_back('0' + z % 10);
        z = z / 10;
    }
    if (sign) {
        s.push_back('-');
    }
    reverse(s.begin(), s.end());
    // cout << s << endl;
    return s;
}
int StringToInt(const string& s) {
    // TODO - you fill in here.
    long int x = 0;
    int start = s[0] == '-' ? 1 : 0;
    for (int i = start; i < s.size(); i++) {
        x *= 10;
        x += s[i] - '0';
    }   
    // cout << x << endl;
    // cout << -x << endl;
    if (start == 1) {
        return -x;
    }
    return x;
}
void Wrapper(int x, const string& s) {
    if (IntToString(x) != s) {
        throw TestFailure("Int to string conversion failed");
    }

    if (StringToInt(s) != x) {
        throw TestFailure("String to int conversion failed");
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x", "s"};
    return GenericTestMain(args, "string_integer_interconversion.cc",
                           "string_integer_interconversion.tsv", &Wrapper,
                           DefaultComparator{}, param_names);
}
