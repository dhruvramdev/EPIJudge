#include "bst_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
#include <memory>
#include <vector>
using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;

// Solution 1 - Slower
bool findPath(const unique_ptr<BstNode<int>>& tree, const unique_ptr<BstNode<int>>& s, vector<BstNode<int>*>& path) {
    if (tree == NULL) {
        return false;
    }

    if (tree.get() == s.get()) {
        path.push_back(tree.get());
        return true;
    }

    bool temp;
    temp = findPath(tree->left, s, path);
    if (temp) {
        path.push_back(tree.get());
        return true;
    }
    temp = findPath(tree->right, s, path);
    if (temp) {
        path.push_back(tree.get());
        return true;
    }
    return false;
}

// Input nodes are nonempty and the key at s is less than or equal to that at b.
BstNode<int>* FindLCASlow(const unique_ptr<BstNode<int>>& tree,
                          const unique_ptr<BstNode<int>>& s,
                          const unique_ptr<BstNode<int>>& b) {

    vector<BstNode<int>*> path1;
    vector<BstNode<int>*> path2;

    findPath(tree, s, path1);
    findPath(tree, b, path2);
    int sa = path1.size() - 1;
    int sb = path2.size() - 1;
    while (path1[sa] == path2[sb] && sb >= 0 && sa >= 0) {
        sa--;
        sb--;
    }

    return path1[sa + 1];
}

BstNode<int>* FindLCA(const unique_ptr<BstNode<int>>& tree,
                      const unique_ptr<BstNode<int>>& s,
                      const unique_ptr<BstNode<int>>& b) {
    if (tree == NULL) {
        return NULL;
    }

    if (tree == s || tree == b) {
        return tree.get();
    }

    BstNode<int>* lcaleft = FindLCA(tree->left, s, b);
    BstNode<int>* lcaright = FindLCA(tree->right, s, b);

    if (lcaleft == NULL && lcaright == NULL) {
        return NULL;
    } else if (lcaleft != NULL && lcaright != NULL) {
        return tree.get();
    } else {
        return lcaright != NULL ? lcaright : lcaleft;
    }
}

int LcaWrapper(TimedExecutor& executor,
               const std::unique_ptr<BstNode<int>>& tree, int key0, int key1) {
    const unique_ptr<BstNode<int>>& node0 = MustFindNode(tree, key0);
    const unique_ptr<BstNode<int>>& node1 = MustFindNode(tree, key1);

    auto result = executor.Run([&] { return FindLCA(tree, node0, node1); });

    if (!result) {
        throw TestFailure("Result can not be nullptr");
    }
    return result->data;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
    return GenericTestMain(args, "lowest_common_ancestor_in_bst.cc",
                           "lowest_common_ancestor_in_bst.tsv", &LcaWrapper,
                           DefaultComparator{}, param_names);
}
