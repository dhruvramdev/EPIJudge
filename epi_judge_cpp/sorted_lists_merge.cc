#include "list_node.h"
#include "test_framework/generic_test.h"

using namespace std;

shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
    // TODO - you fill in here.
    shared_ptr<ListNode<int>> current, past;
    shared_ptr<ListNode<int>> temp;

    if (L1 == NULL) {
        return L2;
    } else if (L2 == NULL) {
        return L1;
    } else {
        if (L1->data > L2->data) {
            temp = L1;
            L1 = L2;
            L2 = temp;
        }
    }

    current = L1;
    past = NULL;
    while (current != NULL && L2 != NULL) {
        if (current->data <= L2->data) {
            past = current;
            current = current->next;
        } else {
            past->next = L2;
            L2 = L2->next;
            past->next->next = current;
            past = past->next;
        }
    }

    if(L2 != NULL){
        past->next = L2;
    }

    return L1;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"L1", "L2"};
    return GenericTestMain(args, "sorted_lists_merge.cc",
                           "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                           DefaultComparator{}, param_names);
}
