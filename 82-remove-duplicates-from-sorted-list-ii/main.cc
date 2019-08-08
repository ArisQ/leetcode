#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "list_node.h"

using namespace std;

class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        ListNode dummy(0);
        ListNode *p = &dummy;
        ListNode *q = head, *r = nullptr;
        int duplicateCount;
        while (q != nullptr) {
            duplicateCount = 0;
            r = q->next;
            while (r != nullptr && r->val == q->val) {
                ++duplicateCount;
                r = r->next;
            }
            if (duplicateCount == 0) {
                p->next = q;
                q->next = nullptr;
                p = p->next;
            }
            q = r;
        }
        return dummy.next;
    }
};

TEST_CASE("Remove Duplicates from Sorted List II - Example 1") {
    ListNode *input = makeList({1, 2, 3, 3, 4, 4, 5});
    ListNode *output = makeList({1, 2, 5});
    REQUIRE(equalList(Solution().deleteDuplicates(input), output));
    freeList(input);
    freeList(output);
}

TEST_CASE("Remove Duplicates from Sorted List II - Example 2") {
    ListNode *input = makeList({1, 1, 1, 2, 3});
    ListNode *output = makeList({2, 3});
    REQUIRE(equalList(Solution().deleteDuplicates(input), output));
    freeList(input);
    freeList(output);
}
