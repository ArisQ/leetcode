#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    int minDepth(TreeNode *root) {
        if (root == nullptr)
            return 0;
        if (root->left == nullptr && root->right == nullptr)
            return 1;
        if (root->left == nullptr)
            return minDepth(root->right) + 1;
        if (root->right == nullptr)
            return minDepth(root->left) + 1;
        return 1 + min(minDepth(root->left), minDepth(root->right));
    }
};

TEST_CASE("Minimum Depth of Binary Tree") {
    auto input = makeTree({3, 9, 20, nullptr, nullptr, 15, 7});
    REQUIRE(Solution().minDepth(input) == 2);
}

TEST_CASE("Minimum Depth of Binary Tree - Wrong Answer 1") {
    auto input = makeTree({1, 2});
    REQUIRE(Solution().minDepth(input) == 2);
}