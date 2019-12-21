#include "test_framework/generic_test.h"
#include <vector>
using namespace std;

void MergeTwoSortedArrays(vector<int>& A, int m, const vector<int>& B, int n) {
    int index = m + n - 1;
    n -= 1;
    m -= 1;

    while (n >= 0 && m >= 0) {
        if (A[m] > B[n]) {
            A[index] = A[m];
            m--;
        } else {
            A[index] = B[n];
            n--;
        }
        index--;
    }

    while (n >= 0) {
        A[index] = B[n];
        n--;
        index--;
    }

    return;
}
vector<int> MergeTwoSortedArraysWrapper(vector<int> A, int m,
                                        const vector<int>& B, int n) {
    MergeTwoSortedArrays(A, m, B, n);
    return A;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"A", "m", "B", "n"};
    return GenericTestMain(
        args, "two_sorted_arrays_merge.cc", "two_sorted_arrays_merge.tsv",
        &MergeTwoSortedArraysWrapper, DefaultComparator{}, param_names);
}
