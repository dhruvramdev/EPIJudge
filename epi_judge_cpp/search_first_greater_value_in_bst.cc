#include "bst_node.h"
#include "test_framework/generic_test.h"
#include <memory>
using std::unique_ptr;

BstNode<int>* FindFirstGreaterThanK(const unique_ptr<BstNode<int>>& tree, int k) {
    if (tree == NULL) {
        return NULL;
    }

    if (tree->data <= k) {
        return FindFirstGreaterThanK(tree->right, k);
    } else if (tree->data > k) {
        auto ptr = FindFirstGreaterThanK(tree->left, k);
        if(ptr == NULL){
            return tree.get();
        }
    }  
}
int FindFirstGreaterThanKWrapper(const unique_ptr<BstNode<int>>& tree, int k) {
    auto result = FindFirstGreaterThanK(tree, k);
    return result ? result->data : -1;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"tree", "k"};
    return GenericTestMain(args, "search_first_greater_value_in_bst.cc",
                           "search_first_greater_value_in_bst.tsv",
                           &FindFirstGreaterThanKWrapper, DefaultComparator{},
                           param_names);
}
