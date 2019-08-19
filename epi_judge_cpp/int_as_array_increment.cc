#include "test_framework/generic_test.h"
#include <vector>
using std::vector;
vector<int> PlusOne(vector<int> A) {
    // TODO - you fill in here.
    int index = A.size() - 1;
    int carry = 1, value;
    while (index >= 0) {
        value = A[index] + carry;
        A[index] = value % 10;
        carry = value / 10;
        if(carry == 0){
            break;
        }
        index--;
    }
    if(carry > 0){
        A.insert(A.begin(), carry);
    }
    return A;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"A"};
    return GenericTestMain(args, "int_as_array_increment.cc",
                           "int_as_array_increment.tsv", &PlusOne,
                           DefaultComparator{}, param_names);
}
