#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "tree_node.h"

using namespace std;

class Solution {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        return buildTree(preorder, inorder, 0, 0, preorder.size());
    }

    TreeNode *buildTree(const vector<int> &preorder,
                        const vector<int> &inorder,
                        int preStart, int inStart, int len) {
        cout << preStart << " " << inStart << " " << len << endl;
        if (len == 0)
            return nullptr;
        auto root = new TreeNode(preorder[preStart]);
        if (len == 1)
            return root;
        int rootIndex = inStart;
        while (preorder[preStart] != inorder[rootIndex]) // 可以用map一次性保存inOrder中的位置，供查询
            ++rootIndex;
        root->left = buildTree(preorder, inorder, preStart + 1, inStart, rootIndex - inStart);
        root->right = buildTree(preorder, inorder, preStart + rootIndex - inStart + 1, rootIndex + 1,
                                inStart + len - rootIndex - 1);
        return root;
    }
};

TEST_CASE("Construct Binary Tree from Preorder and Inorder Traversal") {
    vector<int> preorder{3, 9, 20, 15, 7};
    vector<int> inorder{9, 3, 15, 20, 7};
    auto output = makeTree({3, 9, 20, nullptr, nullptr, 15, 7});
    REQUIRE(equalTree(Solution().buildTree(preorder, inorder), output));
}

TEST_CASE("Construct Binary Tree from Preorder and Inorder Traversal - Wrong Answer 1") {
    vector<int> preorder{};
    vector<int> inorder{};
    auto output = makeTree({});
    REQUIRE(equalTree(Solution().buildTree(preorder, inorder), output));
}

TEST_CASE("Construct Binary Tree from Preorder and Inorder Traversal - Wrong Answer 2") {
    vector<int> preorder{1, 2};
    vector<int> inorder{2, 1};
    auto output = makeTree({1, 2});
    REQUIRE(equalTree(Solution().buildTree(preorder, inorder), output));
}
