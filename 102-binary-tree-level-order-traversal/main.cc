#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode *root) {
        vector<vector<int>> result;
        vector<TreeNode *> layerNodes1, layerNodes2;
        vector<TreeNode *> *layerNode = &layerNodes1, *nextLayerNode = &layerNodes2;
        if (root == nullptr)
            return result;
        result.emplace_back(vector<int>{root->val});
        layerNode->push_back(root);
        while (!layerNode->empty()) {
            vector<int> layerValues;
            nextLayerNode->clear();
            nextLayerNode->reserve(layerNode->size() * 2);
            layerValues.reserve(layerNode->size() * 2);
            for (auto node:*layerNode) {
                if (node->left) {
                    layerValues.push_back(node->left->val);
                    nextLayerNode->push_back(node->left);
                }
                if (node->right) {
                    layerValues.push_back(node->right->val);
                    nextLayerNode->push_back(node->right);
                }
            }
            if (!layerValues.empty())
                result.emplace_back(layerValues);
            swap(layerNode, nextLayerNode);
        }
        return result;
    }
};

TEST_CASE("Binary Tree Level Order Traversal") {
    auto input = makeTree({3, 9, 20, nullptr, nullptr, 15, 7});
    vector<vector<int>> output{
        {3},
        {9,  20},
        {15, 7}
    };
    REQUIRE(Solution().levelOrder(input) == output);
}
