#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include <memory>
#include <queue>
#include <vector>
using namespace std;

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
    // TODO - you fill in here.
    BinaryTreeNode<int>* root = tree.get();
    vector<vector<int>> result = {};

    if (root == NULL) {
        return result;
    }

    int level = 0;
    queue<pair<int, BinaryTreeNode<int>*>> q;
    q.push(make_pair(0, root));

    pair<int, BinaryTreeNode<int>*> t;
    while (!q.empty()) {
        t = q.front();
        q.pop();
        while (result.size() <= t.first) {
            vector<int> p;
            result.push_back(p);
        }

        result[t.first].push_back(t.second->data);

        if (t.second->left != NULL) {
            q.push(make_pair(t.first + 1, t.second->left.get()));
        }
        if (t.second->right != NULL) {
            q.push(make_pair(t.first + 1, t.second->right.get()));
        }
    }

    return result;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"tree"};
    return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                           &BinaryTreeDepthOrder, DefaultComparator{},
                           param_names);
}
