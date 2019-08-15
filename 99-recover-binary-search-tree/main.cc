#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "tree_node.h"

using namespace std;

class Solution {
    TreeNode *previous, *swapLeft, *swapRight;
    bool done;
public:
    void recoverTree(TreeNode *root) {
        previous = nullptr;
        swapLeft = nullptr;
        done = false;
        if (root) {
            inorderTraversal(root);
            cout << swapLeft->val << " " << swapRight->val << endl;
            swap(swapLeft->val, swapRight->val);
        }
    }

    void inorderTraversal(TreeNode *root) {
        if (root->left) {
            inorderTraversal(root->left);
            if (done) return;
        }
        // this node
        if (previous != nullptr && previous->val > root->val) {
            if (swapLeft == nullptr) {
                swapLeft = previous;
                swapRight = root;
            } else {
                swapRight = root;
                done = true;
                return;
            }
        }
        previous = root;
        if (root->right)
            inorderTraversal(root->right);
    }
};

TEST_CASE("Recover Binary Search Tree - Example 1") {
    cout << "Recover Binary Search Tree - Example 1" << endl;
    auto input = makeTree({1, 3, nullptr, nullptr, 2});
    auto output = makeTree({3, 1, nullptr, nullptr, 2});
    cout << input;
    Solution().recoverTree(input);
    cout << input;
    cout << output;
    REQUIRE(equalTree(input, output));
}

TEST_CASE("Recover Binary Search Tree - Example 2") {
    cout << "Recover Binary Search Tree - Example 2" << endl;
    auto input = makeTree({3, 1, 4, nullptr, nullptr, 2});
    auto output = makeTree({2, 1, 4, nullptr, nullptr, 3});
    cout << input;
    Solution().recoverTree(input);
    cout << input;
    cout << output;
    REQUIRE(equalTree(input, output));
}


