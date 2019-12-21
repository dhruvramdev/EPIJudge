#include "test_framework/generic_test.h"
#include <string>
#include <unordered_map>
using std::string;
using std::unordered_map;

bool IsLetterConstructibleFromMagazine(const string& letter_text,
                                       const string& magazine_text) {
    unordered_map<char, int> l;

    for (char c : magazine_text) {
        l[c] += 1;
    }

    for (char c : letter_text) {
        if (l.find(c) == l.end()) {
            return false;
        } else if (l[c] == 0) {
            return false;
        }
        l[c] -= 1;
    }

    return true;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"letter_text", "magazine_text"};
    return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                           "is_anonymous_letter_constructible.tsv",
                           &IsLetterConstructibleFromMagazine,
                           DefaultComparator{}, param_names);
}
