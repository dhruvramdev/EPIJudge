#include "test_framework/generic_test.h"
#include <vector>
using namespace std;

vector<int> IntersectTwoSortedArrays(const vector<int>& A, const vector<int>& B) {
    if (A.size() == 0 || B.size() == 0) {
        return {};
    }
    
    int last = A[0] + 1;
    int index = 0;
    int max = B.size();
    
    vector<int> result;

    for (auto elem : A) {
        if (elem != last) {
            last = elem;
            while(index < max){
                if(B[index] < elem){
                    index++;
                } else if(B[index] == elem){
                    index++;
                    result.push_back(elem);
                    break;
                } else {
                    break;
                }
            }
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"A", "B"};
    return GenericTestMain(
        args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
        &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}
