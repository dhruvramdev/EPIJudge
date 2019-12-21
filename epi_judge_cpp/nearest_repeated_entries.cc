#include "test_framework/generic_test.h"
#include <string>
#include <unordered_map>
#include <vector>
using std::min;
using std::pair;
using std::string;
using std::unordered_map;
using std::vector;

int FindNearestRepetition(const vector<string>& paragraph) {
    unordered_map<string, int> map;
    int curr;
    int ans = INT8_MAX;

    for (int i = 0; i < paragraph.size(); i++) {
        string s = paragraph[i];
        if (map.find(s) == map.end()) {
            map[s] = i;
        } else {
            int curr = i - map[s];
            ans = min(ans, curr);
            map[s] = i;
        }
    }

    return (ans == INT8_MAX) ? -1 : ans;
}


int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"paragraph"};
    return GenericTestMain(args, "nearest_repeated_entries.cc",
                           "nearest_repeated_entries.tsv", &FindNearestRepetition,
                           DefaultComparator{}, param_names);
}
