#include "test_framework/generic_test.h"

#define LEN 65536

unsigned int parity[LEN];
int preCompute() {
    unsigned int p, j;
    for (unsigned int i = 0; i < LEN; i++) {
        p = 0;
        j = i;
        while (j > 0) {
            j = j & (j - 1);
            p = p ^ 1;
        }
        parity[i] = p;
    }
}

short ParityApproach1(unsigned long long x) {
    unsigned int p = 0;
    while(x > 0){
        p = p ^ parity[x & 65535];
        x = x >> 16;
    }
    return p;
}

short Parity(unsigned long long x) {
    x = x ^ (x>>32);
    x = x ^ (x>>16);
    x = x ^ (x>>8);
    x = x ^ (x>>4);
    x = x ^ (x>>2);
    x = x ^ (x>>1);
    return x&1;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x"};
    // preCompute();
    return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                           DefaultComparator{}, param_names);
}
