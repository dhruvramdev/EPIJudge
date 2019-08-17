#include "test_framework/generic_test.h"

unsigned long long Addition(unsigned long long x, unsigned long long y) {
    unsigned long long res = 0;
    unsigned long long c = 0, r = 0;

    int len = 0;
    int a, b;
    while ((x | y) != 0) {
        a = x & 1;
        b = y & 1;

        r = a ^ b ^ c;
        c = (a & b) | (c & (a ^ b));
        res = res | (r << len);

        len++;
        x >>= 1;
        y >>= 1;
    }
    if(c == 1){
        res = res | (c << len);
    }
    return res;
}

unsigned long long Multiply(unsigned long long x, unsigned long long y) {
    unsigned long long t = x;
    unsigned long long res = 0;
    while (y > 0) {
        if (y & 1 == 1) {
            res = Addition(res, x);
        }
        y = y >> 1;
        x = x << 1;
    }
    return res;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x", "y"};
    return GenericTestMain(args, "primitive_multiply.cc",
                           "primitive_multiply.tsv", &Multiply,
                           DefaultComparator{}, param_names);
}
