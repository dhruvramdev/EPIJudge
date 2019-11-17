#include "test_framework/generic_test.h"
#include <queue>
#include <vector>
using namespace std;

// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.
int FindKthLargestMinHeap(int k, vector<int>* A_ptr) {
    priority_queue<int, vector<int>, greater<int>> pq;
    for (auto i = A_ptr->begin(); i != A_ptr->end(); i++) {
        if (pq.size() < k) {
            pq.push(*i);
        } else {
            if (pq.top() < *i) {
                pq.pop();
                pq.push(*i);
            }
        }
    }
    return pq.top();
}

int Helper(int k, vector<int>* A_ptr, int low, int high) {
    int pivot = low + (high - low) / 2;
    int temp;
    temp = (*A_ptr)[high];
    (*A_ptr)[high] = (*A_ptr)[pivot];
    (*A_ptr)[pivot] = temp;

    int pValue = (*A_ptr)[high];
    int start = low;
    int end = high;

    while (start < end) {
        if ((*A_ptr)[start] < pValue) {
            start++;
        } else {
            end--;
            temp = (*A_ptr)[start];
            (*A_ptr)[start] = (*A_ptr)[end];
            (*A_ptr)[end] = temp;
        }
    }
    (*A_ptr)[high] = (*A_ptr)[end];
    (*A_ptr)[end] = pValue;

    temp = high - end + 1;
    if (temp == k) {
        return pValue;
    } else if (temp < k) {
        return Helper(k - temp, A_ptr, low, end - 1);
    } else {
        return Helper(k, A_ptr, end + 1, high);
    }
}

int FindKthLargest(int k, vector<int>* A_ptr) {
    return Helper(k, A_ptr, 0, A_ptr->size() - 1);
}

int FindKthLargestWrapper(int k, vector<int>& A) {
    return FindKthLargest(k, &A);
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"k", "A"};
    return GenericTestMain(args, "kth_largest_in_array.cc",
                           "kth_largest_in_array.tsv", &FindKthLargestWrapper,
                           DefaultComparator{}, param_names);
}
