#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    bool isValidBST(TreeNode *root) {
        cout << root;
        return isValidBST(root, nullptr, nullptr);
    }

    bool isValidBST(TreeNode *root, const int *minVal, const int *maxVal) {
        if (root == nullptr)
            return true;
        if (minVal != nullptr && root->val <= *minVal)
            return false;
        if (maxVal != nullptr && root->val >= *maxVal)
            return false;
        cout << root->val << " min " << (minVal ? *minVal : -1) << " max " << (maxVal ? *maxVal : -1) << endl;
        // minVal < root < maxVal
        return isValidBST(root->left, minVal, maxVal == nullptr ? &root->val : &min(*maxVal, root->val)) &&
               isValidBST(root->right, minVal == nullptr ? &root->val : &max(*minVal, root->val), maxVal);
    }
};

TEST_CASE("Validate Binary Search Tree") {
    REQUIRE(Solution().isValidBST(makeTree({2, 1, 3})) == true);
    REQUIRE(Solution().isValidBST(makeTree({5, 1, 4, nullptr, nullptr, 3, 6})) == false);
    REQUIRE(Solution().isValidBST(makeTree({3, 1, 5, 0, 2, 4, 6})) == true);
}
