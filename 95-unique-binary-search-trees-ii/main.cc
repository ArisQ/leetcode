#define CATCH_CONFIG_MAIN

#include <set>
#include <catch.hpp>
#include "tree_node.h"

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
        os << element;
    }
    os << endl;
    return os;
}

class Solution {
public:
    vector<TreeNode *> generateTrees(int n) {
        if (n == 0)
            return vector<TreeNode *>();
        vector<vector<TreeNode *>> result;
        result.push_back(vector<TreeNode *>{nullptr});
        for (int i = 1; i <= n; ++i) {
            // 左 右
            // 0,n-1   1,n-2   2,n-3     ... n-1,0
            vector<TreeNode *> resultJ;
            for (int j = 0; j < i; ++j) {
                for (auto left:result[j])
                    for (auto right:result[i - j - 1]) {
                        auto root = new TreeNode(j + 1);
                        root->left = copyWithBase(left);
                        root->right = copyWithBase(right, j + 1);
                        resultJ.push_back(root);
                    }
            }
            result.emplace_back(resultJ);
        }
        return result[n];
    }

    TreeNode *copyWithBase(const TreeNode *root, int base = 0) {
        if (root == nullptr)
            return nullptr;
        auto newRoot = new TreeNode(root->val + base);
        newRoot->left = copyWithBase(root->left, base);
        newRoot->right = copyWithBase(root->right, base);
        return newRoot;
    }
};

TEST_CASE("Unique Binary Search Trees II") {
    vector<TreeNode *> output = {
        makeTree({1, nullptr, 3, 2}),
        makeTree({3, 2, nullptr, 1}),
        makeTree({3, 1, nullptr, nullptr, 2}),
        makeTree({2, 1, 3}),
        makeTree({1, nullptr, 2, nullptr, 3})
    };
    cout << "expect output:" << endl << output << endl;
    auto answer = Solution().generateTrees(3);
    cout << "answer:" << endl << answer << endl;
    REQUIRE(multiset<Tree>(answer.begin(), answer.end()) == multiset<Tree>(output.begin(), output.end()));
}
