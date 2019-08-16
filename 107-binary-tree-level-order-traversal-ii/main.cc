#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode *root) {
        vector<TreeNode *> layer1, layer2;
        vector<TreeNode *> *previousLayer = &layer1, *currentLayer = &layer2;
        vector<vector<int>> result;
        if (root == nullptr)
            return result;
        result.emplace_back(vector<int>{root->val});
        previousLayer->push_back(root);
        while (!previousLayer->empty()) {
            vector<int> layerVal;
            currentLayer->clear();
            for (auto node:*previousLayer) {
                if (node->left) {
                    layerVal.push_back(node->left->val);
                    currentLayer->push_back(node->left);
                }
                if (node->right) {
                    layerVal.push_back(node->right->val);
                    currentLayer->push_back(node->right);
                }
            }
            if (!layerVal.empty())
                result.emplace_back(layerVal);
            swap(previousLayer, currentLayer);
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

TEST_CASE("Binary Tree Level Order Traversal II") {
    auto intput = makeTree({3, 9, 20, nullptr, nullptr, 15, 7});
    vector<vector<int>> output{
        {15, 7},
        {9, 20},
        {3}
    };

}
