#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    bool isBalanced(TreeNode *root) {
        return balancedDepth(root) != -1;
    }

    //return depth if balanced else -1
    int balancedDepth(TreeNode *root) {
        if (root == nullptr)
            return 0;
        int left = balancedDepth(root->left);
        int right = balancedDepth(root->right);
        if (left == -1 || right == -1)
            return -1;
        if (left == right + 1 || left == right)
            return left + 1;
        if (right == left + 1)
            return right + 1;
        return -1;
    }
};

TEST_CASE("Balanced Binary Tree - Example 1") {
    auto input = makeTree({3, 9, 20, nullptr, nullptr, 15, 7});
    REQUIRE(Solution().isBalanced(input) == true);
}

TEST_CASE("Balanced Binary Tree - Example 2") {
    auto input = makeTree({1, 2, 2, 3, 3, nullptr, nullptr, 4, 4});
    REQUIRE(Solution().isBalanced(input) == false);
}
