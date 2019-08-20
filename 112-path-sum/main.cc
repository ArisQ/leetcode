#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    bool hasPathSum(TreeNode *root, int sum) {
        cout << root;
        if (root == nullptr)
            return false;
        int remain = sum - root->val;
        if (remain == 0 && root->left == nullptr && root->right == nullptr)
            return true;
        if (root->left && hasPathSum(root->left, remain))
            return true;
        if (root->right && hasPathSum(root->right, remain))
            return true;
        return false;
    }
};

TEST_CASE("Path Sum") {
    auto input = makeTree({5, 4, 8, 11, nullptr, 13, 4, 7, 2, nullptr, nullptr, nullptr, 1});
    REQUIRE(Solution().hasPathSum(input, 22) == true);
}

TEST_CASE("Path Sum - Wrong Answer 1") {
    auto input = makeTree({});
    REQUIRE(Solution().hasPathSum(input, 0) == false);
}

TEST_CASE("Path Sum - Wrong Answer 2") {
    auto input = makeTree({1, 2});
    REQUIRE(Solution().hasPathSum(input, 1) == false);
}