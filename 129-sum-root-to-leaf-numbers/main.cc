#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    int sum;
    int sumNumbers(TreeNode *root) {
        sum = 0;
        if (root == nullptr)
            return sum;
        findNums(0, root);
        return sum;
    }
    void findNums(int pre, TreeNode *root) {
        // root!=nullptr
        int val = pre * 10 + root->val;
        if (root->left == nullptr && root->right == nullptr) {
            sum += val;
            return;
        }
        if (root->left != nullptr)
            findNums(val, root->left);
        if (root->right != nullptr)
            findNums(val, root->right);
    }
};

TEST_CASE("Sum Root to Leaf Numbers") {
    REQUIRE(Solution().sumNumbers(makeTree({1, 2, 3})) == 25);
    REQUIRE(Solution().sumNumbers(makeTree({4, 9, 0, 5, 1})) == 1026);
}
