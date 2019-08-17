#include "test_framework/generic_test.h"
#include "test_framework/random_sequence_checker.h"
#include "test_framework/timed_executor.h"
#include <functional>
#include <random>
#include <vector>
using std::bind;
using std::default_random_engine;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;
int ZeroOneRandom() {
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> dis(0, 1);
    return dis(gen);
}

int UniformRandom(int lower_bound, int upper_bound) {
    int n = upper_bound - lower_bound;
    int outcomes = 1;
    while (outcomes <= n) {
        outcomes <<= 1;
    }
    int tosses = log2(outcomes);
    bool found = false;
    int number;
    while (!found) {
        number = 0;
        for (int i = 0; i < tosses; i++) {
            number <<= 1;
            number = number | ZeroOneRandom();
        }
        if (number <= n) {
            found = true;
        }
    }
    return lower_bound + number;
}


bool UniformRandomRunner(TimedExecutor& executor, int lower_bound,
                         int upper_bound) {
    vector<int> result;
    executor.Run([&] {
        std::generate_n(back_inserter(result), 100000,
                        std::bind(UniformRandom, lower_bound, upper_bound));
    });

    vector<int> sequence;
    std::transform(begin(result), end(result), back_inserter(sequence),
                   [lower_bound](int result) { return result - lower_bound; });
    return CheckSequenceIsUniformlyRandom(result, upper_bound - lower_bound + 1,
                                          0.01);
}

void UniformRandomWrapper(TimedExecutor& executor, int lower_bound,
                          int upper_bound) {
    RunFuncWithRetries(
        bind(UniformRandomRunner, std::ref(executor), lower_bound, upper_bound));
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"executor", "lower_bound",
                                         "upper_bound"};
    return GenericTestMain(args, "uniform_random_number.cc",
                           "uniform_random_number.tsv", &UniformRandomWrapper,
                           DefaultComparator{}, param_names);
}
