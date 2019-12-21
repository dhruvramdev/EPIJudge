#include "bst_node.h"
#include "test_framework/generic_test.h"
#include <memory>
#include <vector>
using std::unique_ptr;
using std::vector;

int k_g = 0;

void Recursive(const unique_ptr<BstNode<int>>& tree, vector<int>& result) {
    if (k_g == 0 || tree == NULL) {
        return;
    }

    Recursive(tree->right, result);
    if (k_g > 0) {
        result.push_back(tree->data);
        k_g--;
    }
    Recursive(tree->left, result);
}

vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>>& tree, int k) {
    vector<int> result;
    k_g = k;
    Recursive(tree, result);
    return result;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"tree", "k"};
    return GenericTestMain(args, "k_largest_values_in_bst.cc",
                           "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                           &UnorderedComparator<std::vector<int>>, param_names);
}
