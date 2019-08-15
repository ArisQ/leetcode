#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    int maxDepth(TreeNode *root) {
        if (root == nullptr)
            return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};

TEST_CASE("Maximum Depth of Binary Tree") {
    auto input = makeTree({3, 9, 20, nullptr, nullptr, 15, 7});
    REQUIRE(Solution().maxDepth(input) == 3);
}
