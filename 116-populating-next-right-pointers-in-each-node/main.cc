#define CATCH_CONFIG_MAIN

#include <queue>
#include <catch.hpp>
#include "tree_node_with_next.h"

using namespace std;

using Node = TreeNodeWithNext;

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() {}

    Node(int _val, Node* _left, Node* _right, Node* _next) {
        val = _val;
        left = _left;
        right = _right;
        next = _next;
    }
};
*/
class Solution {
public:
    Node *connect(Node *root) {
        if (root == nullptr)
            return root;
        queue<Node *> nodes;
        nodes.push(root);
        nodes.push(nullptr); // 层结束标志
        Node dummy(0), *previous = &dummy;
        while (!nodes.empty()) {
            auto node = nodes.front();
            nodes.pop();
            if (node == nullptr) { // layer end marker
                previous = &dummy;
                if (!nodes.empty()) {
                    nodes.push(nullptr);
                }
            } else {
                previous->next = node;
                previous = node;
                if (node->left)
                    nodes.push(node->left);
                if (node->right)
                    nodes.push(node->right);
            }
        }
        return root;
    }
};

TEST_CASE("Populating Next Right Pointers in Each Node") {
    auto input = makeTreeWithNext({1, 2, 3, 4, 5, 6, 7}, false);
    auto output = makeTreeWithNext({1, 2, 3, 4, 5, 6, 7}, true);
    auto answer = Solution().connect(input);
    cout << "output" << endl << output << endl;
    cout << "answer" << endl << answer << endl;
    REQUIRE(equalTreeWithNext(answer, output));
}
