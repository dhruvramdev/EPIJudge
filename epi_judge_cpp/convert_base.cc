#include "test_framework/generic_test.h"
#include <string>
using std::cout;
using std::endl;
using std::string;

string ConvertBase(const string& num_as_string, int b1, int b2) {
    // TODO - you fill in here.
    int start = num_as_string[0] == '-' ? 1 : 0;

    long long int x = 0;
    long long int power = 1;
    char temp;
    int temp1;
    // cout << num_as_string << endl;
    // cout << b1 << endl;
    // cout << b2 << endl;
    for (int i = num_as_string.size() - 1; i >= start; i--) {
        if ('0' <= num_as_string[i] && '9' >= num_as_string[i]) {
            temp1 = num_as_string[i] - '0';
        } else {
            temp1 = num_as_string[i] - 'A' + 10;
        }
        x += power * (temp1);
        power = power * b1;
    }

    if(x == 0){
        return num_as_string;
    }

    // cout << x << endl;
    string nw = start == 1 ? "-" : "";
    power = 1;
    while (power <= x) {
        power = power * b2;
    }
    power = power / b2;
    // cout << power << endl;

    int count = 0;
    while (power != 0) {
        // cout << x << " " << power << endl;
        if (x >= power) {
            x -= power;
            count += 1;
        } else {
            power = power / b2;
            if (count > 9) {
                temp = 'A' + (count - 10);
            } else {
                temp = count + '0';
            }
            nw.push_back(temp);
            count = 0;
        }
    }

    return nw;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
    return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                           &ConvertBase, DefaultComparator{}, param_names);
}
