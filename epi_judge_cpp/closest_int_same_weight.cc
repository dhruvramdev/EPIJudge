#include "test_framework/generic_test.h"
unsigned long long ClosestIntSameBitCount(unsigned long long x) {
    int pos_1 = log2(x & -x);
    unsigned long long bit_mask;
    if (pos_1 == 0) {
        pos_1 = log2((~x) & (-(~x)));
    }
    bit_mask = (1L << (pos_1 - 1)) | (1L << pos_1);
    x ^= bit_mask;
    return x;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x"};
    return GenericTestMain(args, "closest_int_same_weight.cc",
                           "closest_int_same_weight.tsv", &ClosestIntSameBitCount,
                           DefaultComparator{}, param_names);
}
