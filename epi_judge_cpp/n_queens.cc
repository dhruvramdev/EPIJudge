#include "test_framework/generic_test.h"
#include <algorithm>
#include <iterator>
#include <vector>
using std::vector;

vector<vector<int>> result;

void ConvertToSoln(int arr[], int n) {
    vector<int> temp;
    for (int i = 0; i < n; i++) {
        temp.push_back(arr[i]);
    }

    result.push_back(temp);
}

void Solve(int arr[], int placed, int max) {
    if (placed == max) {
        ConvertToSoln(arr, max);
    }

    bool condn;
    for (int i = 0; i < max; i++) {
        condn = true;
        for (int k = 0; k < placed; k++) {
            if (arr[k] == i) {
                condn = false;
                break;
            }
            if (abs(arr[k] - i) == abs(k - placed)) {
                condn = false;
                break;
            }
        }
        if (condn) {
            arr[placed] = i;
            Solve(arr, placed + 1, max);
        }
    }
}

vector<vector<int>> NQueens(int n) {
    result.clear();
    int arr[n] = {0};
    Solve(arr, 0, n);

    return result;
}
bool Comp(vector<vector<int>>& a, vector<vector<int>>& b) {
    std::sort(std::begin(a), std::end(a));
    std::sort(std::begin(b), std::end(b));
    return a == b;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"n"};
    return GenericTestMain(args, "n_queens.cc", "n_queens.tsv", &NQueens, &Comp,
                           param_names);
}
