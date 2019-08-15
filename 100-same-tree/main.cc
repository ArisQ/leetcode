#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if (p == nullptr && q == nullptr)
            return true;
        if (p == nullptr || q == nullptr)
            return false;
        if (p->val != q->val)
            return false;
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

TEST_CASE("Same Tree - Example 1") {
    auto p = makeTree({1, 2, 3});
    auto q = makeTree({1, 2, 3});
    REQUIRE(Solution().isSameTree(p, q) == true);
}

TEST_CASE("Same Tree - Example 2") {
    auto p = makeTree({1, 2});
    auto q = makeTree({1, nullptr, 2});
    REQUIRE(Solution().isSameTree(p, q) == false);
}

TEST_CASE("Same Tree - Example 3") {
    auto p = makeTree({1, 2, 1});
    auto q = makeTree({1, 1, 2});
    REQUIRE(Solution().isSameTree(p, q) == false);
}
