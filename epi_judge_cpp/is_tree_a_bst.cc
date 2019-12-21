#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include <memory>
using std::cout;
using std::endl;
using std::pair;
using std::unique_ptr;

int last;

bool inOrder(const unique_ptr<BinaryTreeNode<int>>& tree) {
    if (tree == NULL) {
        return true;
    }

    bool condn;

    if (tree->left != NULL) {
        condn = inOrder(tree->left);
        if (condn == false) {
            return false;
        }
    }
    if (last > tree->data) {
        return false;
    }
    last = tree->data;

    if (tree->right != NULL) {
        condn = inOrder(tree->right);
        if (condn == false) {
            return false;
        }
    }

    return true;
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
    // if (tree == NULL) {
    //     return true;
    // }
    last = INT32_MIN;
    return inOrder(tree);

    // cout << "######### \n" << endl;
    // cout << "Root : " << tree->data << endl;
    // cout << "Left : ";
    // if (tree->left != NULL) {
    //     cout << tree->left->data;
    // }
    // cout << endl;

    // cout << "Right: ";
    // if (tree->right != NULL) {
    //     cout << tree->right->data;
    // }
    // cout << endl;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"tree"};
    return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                           &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
