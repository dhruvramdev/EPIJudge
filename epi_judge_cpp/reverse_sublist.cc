#include "list_node.h"
#include "test_framework/generic_test.h"

using namespace std;

shared_ptr<ListNode<int>> process(shared_ptr<ListNode<int>> head, int left, int odd) {
    // cout << "Iteration" << endl;
    // cout << head << endl;
    // cout << left << " " << odd << endl;
    shared_ptr<ListNode<int>> tail;
    if (head == NULL) {
        cout << "Error WTF" << endl;
        return NULL;
    }

    if (left == 0) {
        if (odd == 1) {
            tail = head;
        } else {
            tail = head->next;
            int temp = head->data;
            head->data = tail->data;
            tail->data = temp;
        }
    } else {
        tail = process(head->next, left - 1, odd);
        int temp = head->data;
        head->data = tail->data;
        tail->data = temp;
    }
    return tail->next;
}

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
    // TODO - you fill in here.
    // cout << endl;
    // cout << L << endl;
    int diff = finish - start;
    if (diff == 0) {
        return L;
    }

    auto head = L;

    int index = 1;
    while (index < start) {
        head = head->next;
        index++;
    }
    // cout << head << endl;
    // cout << start << " " << finish << endl;
    // cout << diff << endl;

    // diff += 1;
    process(head, diff / 2, (diff + 1) % 2);

    return L;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"L", "start", "finish"};
    return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                           &ReverseSublist, DefaultComparator{}, param_names);
}
