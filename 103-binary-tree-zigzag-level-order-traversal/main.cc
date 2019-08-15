#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
        vector<vector<int>> result;
        vector<TreeNode *> layerNodes1, layerNodes2;
        vector<TreeNode *> *layerNode = &layerNodes1, *nextLayerNode = &layerNodes2;
        if (root == nullptr)
            return result;
        result.emplace_back(vector<int>{root->val});
        layerNode->push_back(root);
        bool reverse = true;
        TreeNode *first, *second;
        while (!layerNode->empty()) {
            vector<int> layerValues;
            nextLayerNode->clear();
            nextLayerNode->reserve(layerNode->size() * 2);
            layerValues.reserve(layerNode->size() * 2);
            for (auto iter = layerNode->crbegin(); iter != layerNode->crend(); ++iter) {
                if (reverse) {
                    first = (*iter)->right;
                    second = (*iter)->left;
                } else {
                    first = (*iter)->left;
                    second = (*iter)->right;
                }
                if (first) {
                    layerValues.push_back(first->val);
                    nextLayerNode->push_back(first);
                }
                if (second) {
                    layerValues.push_back(second->val);
                    nextLayerNode->push_back(second);
                }
            }
            if (!layerValues.empty())
                result.emplace_back(layerValues);
            swap(layerNode, nextLayerNode);
            reverse = !reverse;
        }
        return result;
    }
};

TEST_CASE("Binary Tree Zigzag Level Order Traversal") {
    auto input = makeTree({3, 9, 20, nullptr, nullptr, 15, 7});
    vector<vector<int>> output = {
        {3},
        {20, 9},
        {15, 7}
    };
}
