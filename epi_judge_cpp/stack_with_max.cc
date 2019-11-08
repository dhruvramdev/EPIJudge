#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include <stack>
#include <stdexcept>
using std::length_error;
using std::stack;
class Stack {
  private:
    stack<int> s;
    stack<int> q;
    // Soln acc to book
    // Use Another Stack to keep track changes of max with their consective counts in push since they can be elements that are maximum. 
    // element at top of this stack will be max.

    int max;

    void findMax() {
        int temp;
        max = s.top();
        while (!s.empty()) {
            temp = s.top();

            if (max < temp) {
                max = temp;
            }
            q.push(temp);
            s.pop();
        }
        while (!q.empty()) {
            s.push(q.top());
            q.pop();
        }
    }

  public:
    bool Empty() const {
        return s.empty();
    }
    int Max() const {
        return max;
    }
    int Pop() {
        int temp = s.top();
        s.pop();
        if (temp == max && !s.empty()) {
            findMax();
        }
        return temp;
    }
    void Push(int x) {
        if (s.empty()) {
            max = x;
        } else {
            if (x > max) {
                max = x;
            }
        }
        s.push(x);
        return;
    }
};
struct StackOp {
    std::string op;
    int argument;
};

template <>
struct SerializationTraits<StackOp> : UserSerTraits<StackOp, std::string, int> {
};

void StackTester(const std::vector<StackOp>& ops) {
    try {
        Stack s;
        for (auto& x : ops) {
            if (x.op == "Stack") {
                continue;
            } else if (x.op == "push") {
                s.Push(x.argument);
            } else if (x.op == "pop") {
                int result = s.Pop();
                if (result != x.argument) {
                    throw TestFailure("Pop: expected " + std::to_string(x.argument) +
                                      ", got " + std::to_string(result));
                }
            } else if (x.op == "max") {
                int result = s.Max();
                if (result != x.argument) {
                    throw TestFailure("Max: expected " + std::to_string(x.argument) +
                                      ", got " + std::to_string(result));
                }
            } else if (x.op == "empty") {
                int result = s.Empty();
                if (result != x.argument) {
                    throw TestFailure("Empty: expected " + std::to_string(x.argument) +
                                      ", got " + std::to_string(result));
                }
            } else {
                throw std::runtime_error("Unsupported stack operation: " + x.op);
            }
        }
    } catch (length_error&) {
        throw TestFailure("Unexpected length_error exception");
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"ops"};
    return GenericTestMain(args, "stack_with_max.cc", "stack_with_max.tsv",
                           &StackTester, DefaultComparator{}, param_names);
}
