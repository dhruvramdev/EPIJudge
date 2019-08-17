#include "test_framework/generic_test.h"

unsigned long long ReverseBits(unsigned long long x) {
    unsigned long long bit_mask = 0L;
    unsigned long long one = 1L;
    int j;
    for (int i = 0; i < 32; i++) {
        j = 63 - i;
        if (((x >> i) & 1) != ((x >> j) & 1)) {
            bit_mask |= one << i;
            bit_mask |= one << j;
        }
    }

    return bit_mask ^ x;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x"};
    return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                           &ReverseBits, DefaultComparator{}, param_names);
}
