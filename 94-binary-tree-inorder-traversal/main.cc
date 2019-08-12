#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "tree_node.h"

using namespace std;

ostream &operator<<(ostream &os, const vector<int> &array) {
    for (auto element:array) {
        os.width(3);
        os << element;
    }
    os << endl;
    return os;
}

class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> result;
        vector<TreeNode *> treeNodeStack;
        TreeNode *todo = root;
        while ((todo != nullptr) || (!treeNodeStack.empty())) {
            if (!todo) {
                todo = treeNodeStack.back();
                treeNodeStack.pop_back();
                result.push_back(todo->val);
                todo = todo->right;
                continue;
            }
            if (todo->left) {
                treeNodeStack.push_back(todo);
                todo = todo->left;
                continue;
            }
            result.push_back(todo->val);
            todo = todo->right;
        }
        return result;
    }
};

TEST_CASE("Binary Tree Inorder Traversal") {
    TreeNode *node1 = new TreeNode(1);
    TreeNode *node2 = new TreeNode(2);
    TreeNode *node3 = new TreeNode(3);
    node1->right = node2;
    node2->left = node3;
    auto input = node1;
    vector<int> output{1, 3, 2};
    REQUIRE(Solution().inorderTraversal(input) == output);
}

