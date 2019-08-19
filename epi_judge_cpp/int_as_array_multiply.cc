#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

void AddMul(vector<int>& A, vector<int>& B, int start, int mul) {
    // Does A = A + B
    // where B is multiplied by mul

    int carry = 0;
    int i = start;
    int limit = B.size() + start;
    while (i < limit) {
        A[i] = A[i] + (B[i-start] * mul) + carry;
        carry = A[i] / 10;
        A[i] = A[i] % 10;
        i++;
    }
    while (i < A.size() && carry > 0) {
        A[i] = A[i] + carry;
        carry = A[i] / 10;
        A[i] = A[i] % 10;
        i++;
    }
    if (carry > 0) {
        A.push_back(carry);
    }
}

vector<int> Multiply(vector<int> num1, vector<int> num2) {
    int a = num1.size();
    int b = num2.size();
    bool negative = false;
    if (num1[0] < 0) {
        negative = !negative;
        num1[0] = -num1[0];
    }
    if (num2[0] < 0) {
        negative = !negative;
        num2[0] = -num2[0];
    }
    vector<int> result(a + b, 0);
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    for (int i = 0; i < a; i++) {
        AddMul(result, num2, i, num1[i]);
    }

    // Remove Trailing Zereos
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }

    reverse(result.begin(), result.end());

    // Add Sign
    if (negative) {
        result[0] = -result[0];
    }
    return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};
  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
