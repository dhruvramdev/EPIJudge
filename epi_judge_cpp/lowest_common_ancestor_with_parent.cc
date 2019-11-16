#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
#include "vector"

using namespace std;

BinaryTreeNode<int>* LCAMoreSpace(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
    
    vector<BinaryTreeNode<int>*> v1;
    vector<BinaryTreeNode<int>*> v2;

    BinaryTreeNode<int>* temp;
    temp = node0.get();
    v1.push_back(temp);
    while(temp->parent != NULL){
        temp = temp->parent;
        v1.push_back(temp);
    }
    
    temp = node1.get();
    v2.push_back(temp);
    while(temp->parent != NULL){
        temp = temp->parent;
        v2.push_back(temp);
    }
    int sa = v1.size() - 1;
    int sb = v2.size() - 1;
    while (v1[sa] == v2[sb] && sb >= 0 && sa >= 0) {
        sa--;
        sb--;
    }
    return v1[sa + 1];
}

BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
    
    int depth1 = 0;
    int depth2 = 0;


    BinaryTreeNode<int> *temp, *temp1;
    temp = node0.get();
    depth1++;
    while(temp->parent != NULL){
        temp = temp->parent;
        depth1++;
    }
    
    temp = node1.get();
    depth2++;
    while(temp->parent != NULL){
        temp = temp->parent;
        depth2++;
    }

    if(depth1 < depth2){
        temp = node1.get();
        temp1 = node0.get();
    } else {
        temp = node0.get();
        temp1 = node1.get();
    }

    int dd = abs(depth2 - depth1);
    while(dd--){
        temp = temp->parent;
    }

    while(temp != temp1){
        temp = temp->parent;
        temp1 = temp1->parent;
    }

    return temp;
}


int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
    const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
    const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

    auto result = executor.Run([&] { return LCA(node0, node1); });

    if (!result) {
        throw TestFailure("Result can not be nullptr");
    }
    return result->data;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
    return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                           "lowest_common_ancestor.tsv", &LcaWrapper,
                           DefaultComparator{}, param_names);
}
