#include "test_framework/generic_test.h"
long long SwapBits(long long x, int i, int j) {
    unsigned long long int vi = (x >> i) & 1;
    unsigned long long int vj = (x >> j) & 1;
    unsigned long long int one = 1;

    if (vi != vj) {
        unsigned long long int m = ~(one << j);
        x = (x & m) | (vi << j);
        m = ~(one << i);
        x = (x & m) | (vj << i);
    }
    return x;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x", "i", "j"};
    return GenericTestMain(args, "swap_bits.cc", "swap_bits.tsv", &SwapBits,
                           DefaultComparator{}, param_names);
}
