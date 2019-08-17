#include "test_framework/generic_test.h"

long long Reverse(int x) {
    long long r = 0;
    while (x != 0) {
        r *= 10;
        r += x % 10;
        x = x / 10;
    }
    return r;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x"};
    return GenericTestMain(args, "reverse_digits.cc", "reverse_digits.tsv",
                           &Reverse, DefaultComparator{}, param_names);
}
