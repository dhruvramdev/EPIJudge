#include "test_framework/generic_test.h"
#include <queue>
#include <vector>
using namespace std;

vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> p;

    int no_arrays = sorted_arrays.size();
    int indexes[no_arrays];
    for (int i = 0 ; i < no_arrays ; i++) {
        indexes[i] = 1;
        p.push(make_pair(sorted_arrays[i][0], i));
    }
    vector<int> result;
    pair<int, int> temp;
    while (!p.empty()) {
        temp = p.top();
        p.pop();
        result.push_back(temp.first);
        if (indexes[temp.second] < sorted_arrays[temp.second].size()) {
            p.push(make_pair(sorted_arrays[temp.second][indexes[temp.second]], temp.second));
            indexes[temp.second]++;
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"sorted_arrays"};
    return GenericTestMain(args, "sorted_arrays_merge.cc",
                           "sorted_arrays_merge.tsv", &MergeSortedArrays,
                           DefaultComparator{}, param_names);
}
