#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using namespace std;

int getHeight(const unique_ptr<BinaryTreeNode<int>>& tree){
    if (tree == NULL) {
        return 0;
    }

    int h1 = getHeight(tree->left);
    if(h1 == -1){
        return -1;
    }
    int h2 = getHeight(tree->right);
    if(h2 == -1){
        return -1;
    }

    if(abs(h1- h2) <= 1){
        return max(h1, h2) + 1;
    }
    return -1;
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
    // TODO - you fill in here.
    if (tree == NULL) {
        return true;
    }

    int h = getHeight(tree);
    if(h == -1){
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"tree"};
    return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                           &IsBalanced, DefaultComparator{}, param_names);
}
