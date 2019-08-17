#include "test_framework/generic_test.h"
bool IsPalindromeNumber(int x) {
    if (x < 0) {
        return false;
    }
    long long original = x;
    long long r = 0;
    while (x != 0) {
        r *= 10;
        r += x % 10;
        x = x / 10;
    }
    return r == original;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x"};
    return GenericTestMain(args, "is_number_palindromic.cc",
                           "is_number_palindromic.tsv", &IsPalindromeNumber,
                           DefaultComparator{}, param_names);
}
