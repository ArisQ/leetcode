#define CATCH_CONFIG_MAIN

#include <unordered_map>
#include <catch.hpp>
#include "tree_node.h"

using namespace std;

class Solution {
    unordered_map<int, int> inOrderIndex;
public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        for (int i = inorder.size() - 1; i >= 0; --i)
            inOrderIndex.insert({inorder[i], i});
        return buildTree(inorder, postorder, 0, 0, inorder.size());

    }

    TreeNode *buildTree(const vector<int> &inorder,
                        const vector<int> &postorder,
                        int inStart, int postStart, int len) {
        cout << inStart << " " << postStart << " " << len << endl;

        if (len == 0)
            return nullptr;

        auto root = new TreeNode(postorder[postStart + len - 1]);
        if (len == 1)
            return root;
        int rootIndex = inOrderIndex[root->val];
        root->left = buildTree(inorder, postorder, inStart, postStart, rootIndex - inStart);
        root->right = buildTree(inorder, postorder, rootIndex + 1, postStart + rootIndex - inStart,
                                inStart + len - rootIndex - 1);
        return root;
    }
};

TEST_CASE("Construct Binary Tree from Inorder and Postorder Traversal") {
    vector<int> inorder{9, 3, 15, 20, 7};
    vector<int> postorder{9, 15, 7, 20, 3};
    auto output = makeTree({3, 9, 20, nullptr, nullptr, 15, 7});
    REQUIRE(equalTree(Solution().buildTree(inorder, postorder), output));
}
