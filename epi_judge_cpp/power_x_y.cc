#include "test_framework/generic_test.h"
#include <unordered_map>

std::unordered_map<int, double> m;

double Power(double x, int y) {
    if (y == 0) {
        return 1.0;
    } else if (y == 1) {
        return x;
    } else if (y == -1) {
        return 1.0 / x;
    }
    double temp;
    temp = Power(x, y / 2);
    if (y % 2 == 0) {
        temp = temp * temp;
    } else {
        if (y < 0) {
            temp = (temp * temp) / x;
        } else {
            temp = temp * temp * x;
        }
    }
    return temp;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"x", "y"};
    return GenericTestMain(args, "power_x_y.cc", "power_x_y.tsv", &Power,
                           DefaultComparator{}, param_names);
}
