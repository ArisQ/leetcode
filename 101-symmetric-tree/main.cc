#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        if (root == nullptr)
            return true;
        return isMirror(root->left, root->right);
    }

    bool isMirror(TreeNode *p, TreeNode *q) {
        if (p == nullptr && q == nullptr)
            return true;
        if (p == nullptr || q == nullptr)
            return false;
        if (p->val != q->val)
            return false;
        return isMirror(p->left, q->right) && isMirror(p->right, q->left);
    }
};

TEST_CASE("Symmetric Tree - Example 1") {
    auto input = makeTree({1, 2, 2, 3, 4, 4, 3});
    REQUIRE(Solution().isSymmetric(input) == true);
}

TEST_CASE("Symmetric Tree - Example 2") {
    auto input = makeTree({1, 2, 2, nullptr, 3, nullptr, 3});
    REQUIRE(Solution().isSymmetric(input) == false);
}

