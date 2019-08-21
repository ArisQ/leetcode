#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    void flatten(TreeNode *root) {
        cout << root;
        if (root == nullptr)
            return;
        flattenTree(root);
        cout << root;
    }

    // return tail
    TreeNode *flattenTree(TreeNode *root) {
        assert(root != nullptr);
        if (root->left == nullptr && root->right == nullptr)
            return root;
        TreeNode *leftTail = nullptr, *rightTail = nullptr;
        if (root->right)
            rightTail = flattenTree(root->right);
        if (root->left) {
            leftTail = flattenTree(root->left);
            leftTail->right = root->right;
            root->right = root->left;
            root->left = nullptr;
        }
        return rightTail ? rightTail : leftTail;
    }
};

TEST_CASE("Flatten Binary Tree to Linked List") {
    auto input = makeTree({1, 2, 5, 3, 4, nullptr, 6});
    auto output = makeTree({1, nullptr, 2, nullptr, 3, nullptr, 4, nullptr, 5, nullptr, 6});
    Solution().flatten(input);
    REQUIRE(equalTree(input, output));
}

TEST_CASE("Flatten Binary Tree to Linked List - Empty") {
    auto input = makeTree({});
    auto output = makeTree({});
    Solution().flatten(input);
    REQUIRE(equalTree(input, output));
}
