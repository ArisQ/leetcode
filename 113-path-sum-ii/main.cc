#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "tree_node.h"

using namespace std;

class Solution {
    vector<int> path;
    vector<vector<int>> result;
public:
    vector<vector<int>> pathSum(TreeNode *root, int sum) {
        if (root == nullptr)
            return result;
        findPathSum(root, sum);
        return result;
    }

    void findPathSum(TreeNode *root, int sum) {
        assert(root != nullptr);
        path.push_back(root->val);
        int remain = sum - root->val;
        if (root->left == nullptr && root->right == nullptr) {//leaf
            if (remain == 0)
                result.push_back(path);
        } else { // not leaf
            if (root->left)
                findPathSum(root->left, remain);
            if (root->right)
                findPathSum(root->right, remain);
        }
        path.pop_back();
    }
};

TEST_CASE("Path Sum II") {
    auto input = makeTree({5, 4, 8, 11, nullptr, 13, 4, 7, 2, nullptr, nullptr, 5, 1});
    vector<vector<int>> output{
        {5, 4, 11, 2},
        {5, 8, 4,  5}
    };
    REQUIRE(Solution().pathSum(input, 22) == output);
}

TEST_CASE("Path Sum II - Empty") {
    auto input = makeTree({});
    vector<vector<int>> output{};
    REQUIRE(Solution().pathSum(input, 0) == output);
}

TEST_CASE("Path Sum II - Not leaf") {
    auto input = makeTree({1, 2});
    vector<vector<int>> output{};
    REQUIRE(Solution().pathSum(input, 1) == output);
}

