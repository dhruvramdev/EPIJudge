#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
#include <memory>
using std::shared_ptr;
using std::cout;
using std::endl;

shared_ptr<ListNode<int>> HasCycle(const shared_ptr<ListNode<int>>& head) {
    // TODO - you fill in here.
    // cout << head << endl;
    auto slow = head;
    auto fast = head;

    bool flag = false;
    int looplength = 0;

    while (fast != NULL && slow != NULL) {
        // cout << fast << endl;
        // cout << slow << endl;

        fast = fast->next;
        if (fast != NULL) {
            fast = fast->next;
        } else {
            break;
        }
        slow = slow->next;

        if (fast == slow) {
            flag = true;
            fast = fast->next;
            looplength = 1;
            while (fast != slow) {
                fast = fast->next;
                looplength += 1;
            }
            break;
        }
    }

    if (flag) {
        fast = head;
        slow = head;
        while (looplength--) {
            fast = fast->next;
        }

        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }
        return fast;
    }

    return NULL;
}
void HasCycleWrapper(TimedExecutor& executor,
                     const shared_ptr<ListNode<int>>& head, int cycle_idx) {
    int cycle_length = 0;
    if (cycle_idx != -1) {
        if (!head) {
            throw std::runtime_error("Can't cycle empty list");
        }
        shared_ptr<ListNode<int>> cycle_start, cursor = head;
        while (cursor->next) {
            if (cursor->data == cycle_idx) {
                cycle_start = cursor;
            }
            cursor = cursor->next;
            cycle_length += !!cycle_start;
        }
        if (cursor->data == cycle_idx) {
            cycle_start = cursor;
        }
        if (!cycle_start) {
            throw std::runtime_error("Can't find a cycle start");
        }
        cursor->next = cycle_start;
        cycle_length++;
    }
    shared_ptr<ListNode<int>> result =
        executor.Run([&] { return HasCycle(head); });

    if (cycle_idx == -1) {
        if (result != nullptr) {
            throw TestFailure("Found a non-existing cycle");
        }
    } else {
        if (result == nullptr) {
            throw TestFailure("Existing cycle was not found");
        }

        auto cursor = result;
        do {
            cursor = cursor->next;
            cycle_length--;
            if (!cursor || cycle_length < 0) {
                throw TestFailure(
                    "Returned node does not belong to the cycle or is not the "
                    "closest node to the head");
            }
        } while (cursor != result);

        if (cycle_length != 0) {
            throw TestFailure(
                "Returned node does not belong to the cycle or is not the closest "
                "node to the head");
        }
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"executor", "head", "cycle_idx"};
    return GenericTestMain(args, "is_list_cyclic.cc", "is_list_cyclic.tsv",
                           &HasCycleWrapper, DefaultComparator{}, param_names);
}
