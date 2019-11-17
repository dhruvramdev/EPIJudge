#include "test_framework/generic_test.h"
#include <vector>
using std::vector;

int SearchFirstOfK(const vector<int>& A, int k) {
    int low = 0;
    int high = A.size() - 1;
    int occurance = A.size();
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (A[mid] == k) {
            occurance = mid;
            high = mid - 1;
        } else if (A[mid] > k) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return occurance == A.size() ? -1 : occurance;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"A", "k"};
    return GenericTestMain(args, "search_first_key.cc", "search_first_key.tsv",
                           &SearchFirstOfK, DefaultComparator{}, param_names);
}
