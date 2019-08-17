#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    TreeNode *sortedArrayToBST(vector<int> &nums) {
        auto result = sortedArrayToBST(nums, 0, nums.size());
        cout << result;
        return result;
    }
    TreeNode *sortedArrayToBST(const vector<int> &nums, int start, int end) {
        cout << start << " " << end << endl;
        if (start == end)
            return nullptr;
        if (start + 1 == end)
            return new TreeNode(nums[start]);
        int middle = (start + end) / 2;
        auto root = new TreeNode(nums[middle]);
        root->left = sortedArrayToBST(nums, start, middle);
        root->right = sortedArrayToBST(nums, middle + 1, end);
        return root;
    }
};

TEST_CASE("Convert Sorted Array to Binary Search Tree") {
    vector<int> input{-10, -3, 0, 5, 9};
    auto output = makeTree({0, -3, 9, -10, nullptr, 5});
    REQUIRE(equalTree(Solution().sortedArrayToBST(input), output));
}
