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
        Node dummy(0, nullptr, nullptr, nullptr);
        Node *head = &dummy;
        Node *previous = &dummy;
        for (Node *iter = root; iter != nullptr; iter = iter->next) {
            if (iter->left) {
                previous->next = iter->left;
                previous = iter->left;
            }
            if (iter->right) {
                previous->next = iter->right;
                previous = iter->right;
            }
        }
        connect(head->next);
        return root;
    }
};
TEST_CASE("Populating Next Right Pointers in Each Node II") {
    auto input = makeTreeWithNext({1, 2, 3, 4, 5, nullptr, 7}, false);
    auto output = makeTreeWithNext({1, 2, 3, 4, 5, nullptr, 7}, true);
    auto answer = Solution().connect(input);
    cout << "output" << endl << output << endl;
    cout << "answer" << endl << answer << endl;
    REQUIRE(equalTreeWithNext(answer, output));
}

TEST_CASE("Populating Next Right Pointers in Each Node II - Case 2") {
    auto input = makeTreeWithNext({2, 1, 3, 0, 7, 9, 1, 2, nullptr, 1, 0, nullptr, nullptr,
                                   8, 8, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 7}, false);
    auto output = makeTreeWithNext({2, 1, 3, 0, 7, 9, 1, 2, nullptr, 1, 0, nullptr, nullptr,
                                    8, 8, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, 7}, true);
    auto answer = Solution().connect(input);
    cout << "output" << endl << output << endl;
    cout << "answer" << endl << answer << endl;
    REQUIRE(equalTreeWithNext(answer, output));
}
