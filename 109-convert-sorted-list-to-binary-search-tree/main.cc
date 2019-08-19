#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "list_node.h"
#include "tree_node.h"

using namespace std;

class Solution {
public:
    TreeNode *sortedListToBST(ListNode *head) {
        vector<ListNode *> nodes;
        while (head != nullptr) {
            nodes.push_back(head);
            head = head->next;
        }
        return sortedArrayToBST(nodes, 0, nodes.size());
    }

    TreeNode *sortedArrayToBST(vector<ListNode *> &nodes, int start, int end) {
        if (start == end)
            return nullptr;
        if (start + 1 == end)
            return new TreeNode(nodes[start]->val);
        int middle = (start + end) / 2;
        auto root = new TreeNode(nodes[middle]->val);
        root->left = sortedArrayToBST(nodes, start, middle);
        root->right = sortedArrayToBST(nodes, middle + 1, end);
        return root;
    }
};

TEST_CASE("Convert Sorted List to Binary Search Tree") {
    auto input = makeList({-10, -3, 0, 5, 9});
    auto output = makeTree({0, -3, 9, -10, nullptr, 5});
    REQUIRE(equalTree(Solution().sortedListToBST(input), output));
}
