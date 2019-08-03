#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "list_node.h"

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k) {
        if (head == nullptr)
            return head;
        ListNode *tail = head, *p = head;
        int size = 1;
        while (tail->next != nullptr) {
            tail = tail->next;
            ++size;
        }
        k = k % size;
        if (k == 0)
            return head;
        for (int i = size - k - 1; i > 0; --i) {
            p = p->next;
        }
        tail->next = head;
        head = p->next;
        p->next = nullptr;
        return head;
    }
};

TEST_CASE("Rotate List - Example 1") {
    auto input = makeList({1, 2, 3, 4, 5});
    auto output = makeList({4, 5, 1, 2, 3});
    REQUIRE(equalList(Solution().rotateRight(input, 2), output));
}

TEST_CASE("Rotate List - Example 2") {
    auto input = makeList({0, 1, 2});
    auto output = makeList({2, 0, 1});
    REQUIRE(equalList(Solution().rotateRight(input, 4), output));
}

TEST_CASE("Rotate List - Empty 1") {
    auto input = makeList({});
    auto output = makeList({});
    REQUIRE(equalList(Solution().rotateRight(input, 0), output));
}
TEST_CASE("Rotate List - Empty 2") {
    auto input = makeList({});
    auto output = makeList({});
    REQUIRE(equalList(Solution().rotateRight(input, 1), output));
}
TEST_CASE("Rotate List - Single 1") {
    auto input = makeList({0});
    auto output = makeList({0});
    REQUIRE(equalList(Solution().rotateRight(input, 0), output));
}
TEST_CASE("Rotate List - Single 2") {
    auto input = makeList({0});
    auto output = makeList({0});
    REQUIRE(equalList(Solution().rotateRight(input, 1), output));
}
TEST_CASE("Rotate List - Double 1") {
    auto input = makeList({0, 1});
    auto output = makeList({0, 1});
    REQUIRE(equalList(Solution().rotateRight(input, 0), output));
}
TEST_CASE("Rotate List - Double 2") {
    auto input = makeList({0, 1});
    auto output = makeList({1, 0});
    REQUIRE(equalList(Solution().rotateRight(input, 1), output));
}
TEST_CASE("Rotate List - Double 3") {
    auto input = makeList({0, 1});
    auto output = makeList({0, 1});
    REQUIRE(equalList(Solution().rotateRight(input, 2), output));
}