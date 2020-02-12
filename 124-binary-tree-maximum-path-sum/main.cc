#define CATCH_CONFIG_MAIN

#include <catch.hpp>

#include "tree_node.h"

using namespace std;

class Solution {
    int result = 0;
public:
    int maxPathSum(TreeNode *root) {
        // no empty tree
        result = root->val;
        maxTreeSum(root);
        return result;
    }
    int maxTreeSum(TreeNode *root) {
        assert(root != nullptr);
        int left = 0;
        int right = 0;
        if (root->left)
            left = maxTreeSum(root->left);
        if (root->right)
            right = maxTreeSum(root->right);
        /* 单root
         * root+left
         * root+right
         * left+root+right(起点终点都有，结束)
         */
        int sum = root->val + max(0, max(left, right));
        if (sum > result) result = sum;
        int total = root->val + left + right;
        if (total > result) result = total; // total即使最大也不返回，因为不能有三岔
        return sum;
    }
};

TEST_CASE("Binary Tree Maximum Path Sum") {
    REQUIRE(Solution().maxPathSum(makeTree({1, 2, 3})) == 6);
    REQUIRE(Solution().maxPathSum(makeTree({-10, 9, 20, nullptr, nullptr, 15, 7})) == 42);
    REQUIRE(Solution().maxPathSum(makeTree({-3})) == -3);
    REQUIRE(Solution().maxPathSum(makeTree({1, -2, -3, 1, 3, -2, nullptr, -1})) == 3);
    REQUIRE(Solution().maxPathSum(makeTree({5, 4, 8, 11, nullptr, 13, 4, 7, 2, nullptr, nullptr, nullptr, 1})) == 48);
}
