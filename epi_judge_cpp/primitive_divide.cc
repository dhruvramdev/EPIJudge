#include "test_framework/generic_test.h"

int Divide(int x, int y) {
    long long int count = 0;
    long long int divisor = 1;
    long long int token = y;
    while (token <= x) {
        token = token << 1;
        divisor = divisor << 1;
    }

    while (x >= y) {
        if (token <= x) {
            x -= token;
            count += divisor;
        } else {
            token = token >> 1;
            divisor = divisor >> 1;
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x", "y"};
    return GenericTestMain(args, "primitive_divide.cc", "primitive_divide.tsv",
                           &Divide, DefaultComparator{}, param_names);
}
