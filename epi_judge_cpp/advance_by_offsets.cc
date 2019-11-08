#include "test_framework/generic_test.h"
#include <algorithm>
#include <vector>
using std::min;
using std::vector;
using namespace std;

bool CanReachEnd(const vector<int>& max_advance_steps) {
    // TODO - you fill in here.
    int size = max_advance_steps.size();
    int temp;
    int arr[size] = {0};

    int count = 0;
    temp = max_advance_steps[0];
    arr[0] += 1;
    if ((temp + 1) < size) {
        arr[temp + 1] += -1;
    }

    for (int i = 1; i < size; i++) {
        temp = max_advance_steps[i];
        
        arr[i] += 1;
        if ((i + temp + 1) < size) {
            arr[i + temp + 1] += -1;
        }

        arr[i] = arr[i - 1] + arr[i];
        if (arr[i] == 1) {
            count++;
        }
    }

    // cout << endl;
    // for (int i = 0; i < size; i++) {
    // cout << arr[i] << " ";
    // }
    // cout << endl;
    // cout << count << endl;

    return count == 0;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"max_advance_steps"};
    return GenericTestMain(args, "advance_by_offsets.cc",
                           "advance_by_offsets.tsv", &CanReachEnd,
                           DefaultComparator{}, param_names);
}
