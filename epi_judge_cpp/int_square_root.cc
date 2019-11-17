#include "test_framework/generic_test.h"
using namespace std;

int SquareRoot(int k) {
    if(k == 0 || k == 1){
        return k;
    }
    int start = 0;
    int end = k / 2;
    long long int mid;
    int result;
    while (start <= end) {
        mid = start + (end - start) / 2;
        if (mid * mid <= k) {
            result = mid;
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"k"};
    return GenericTestMain(args, "int_square_root.cc", "int_square_root.tsv",
                           &SquareRoot, DefaultComparator{}, param_names);
}
