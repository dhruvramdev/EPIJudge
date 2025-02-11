#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
#include <iterator>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

int ReplaceAndRemove(int size, char s[]) {
    int index = 0;
    int new_size = 0;

    for (int i = 0; i < size; i++) {
        if (s[i] == 'a') {
            new_size += 1;
        }
        
        if (s[i] == 'b') {

        } else {
            s[index] = s[i];
            index++;
        }

    }
    size = index;
    new_size = size + new_size;
    index = new_size - 1;

    for (int i = size - 1; i >= 0; i--) {
        if (s[i] == 'a') {
            s[index] = 'd';
            index--;
            s[index] = 'd';
            index--;
        } else {
            s[index] = s[i];
            index--;
        }
    }

    return new_size;
}
vector<string> ReplaceAndRemoveWrapper(TimedExecutor& executor, int size,
                                       const vector<string>& s) {
    std::vector<char> s_copy(s.size(), '\0');
    for (int i = 0; i < s.size(); ++i) {
        if (!s[i].empty()) {
            s_copy[i] = s[i][0];
        }
    }

    int res_size =
        executor.Run([&] { return ReplaceAndRemove(size, s_copy.data()); });

    vector<string> result;
    for (int i = 0; i < res_size; ++i) {
        result.emplace_back(string(1, s_copy[i]));
    }
    return result;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"executor", "size", "s"};
    return GenericTestMain(args, "replace_and_remove.cc",
                           "replace_and_remove.tsv", &ReplaceAndRemoveWrapper,
                           DefaultComparator{}, param_names);
}
