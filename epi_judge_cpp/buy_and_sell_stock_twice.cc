#include "test_framework/generic_test.h"
#include <vector>
using std::vector;
using std::cout;
using std::endl;  
double BuyAndSellStockTwice(vector<double>& prices) {
    // TODO - you fill in here.
    int n = prices.size();
    for (int i = n - 1; i > 0; i--) {
        prices[i] = prices[i] - prices[i - 1];
    }
    prices[0] = 0;

    double max_sum = 0;
    double second_sum = 0;
    double current_sum = 0;

    for (int i = 0; i < n; i++) {
        current_sum += prices[i];
        if (current_sum < 0) {
            current_sum = 0;
        }
        if (current_sum > second_sum) {
            if(current_sum > max_sum){
                second_sum = max_sum;
                max_sum = current_sum;
            } else {
                second_sum = current_sum;
            }
        }
    }

    if(second_sum == 0){
        second_sum = current_sum;
    }
    cout << second_sum << " " << max_sum << endl;

    return max_sum + second_sum;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"prices"};
    return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                           "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                           DefaultComparator{}, param_names);
}
