#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "list_node.h"

using namespace std;

class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        ListNode *p = head, *q = head;
        while (p != nullptr) {
            while (q != nullptr && q->val == p->val)
                q = q->next;
            p->next = q;
            p = q;
        }
        return head;
    }
};

TEST_CASE("Remove Duplicates from Sorted List - Example 1") {
    ListNode *input = makeList({1, 1, 2});
    ListNode *output = makeList({1, 2});
    REQUIRE(equalList(Solution().deleteDuplicates(input), output));
    freeList(input);
    freeList(output);
}

TEST_CASE("Remove Duplicates from Sorted List - Example 2") {
    ListNode *input = makeList({1, 1, 2, 3, 3});
    ListNode *output = makeList({1, 2, 3});
    REQUIRE(equalList(Solution().deleteDuplicates(input), output));
    freeList(input);
    freeList(output);
}

