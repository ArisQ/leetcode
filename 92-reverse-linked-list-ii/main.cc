#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "list_node.h"

using namespace std;

class Solution {
public:
    ListNode *reverseBetween(ListNode *head, int m, int n) {
        // 1 ≤ m ≤ n ≤ length
        ListNode dummy(0);
        ListNode *p = &dummy;
        dummy.next = head;
        for (int i = 1; i < m; ++i)
            p = p->next;
        ListNode *pre = p, *q = p->next, *temp = nullptr;
        for (int i = m; m <= n; ++m) {
            temp = q->next;
            q->next = pre;
            pre = q;
            q = temp;
        }
        p->next->next = q;
        p->next = pre;
        cout << dummy.next << endl;
        return dummy.next;
    }
};

TEST_CASE("Reverse Linked List II") {
    ListNode *input = makeList({1, 2, 3, 4, 5});
    ListNode *output = makeList({1, 4, 3, 2, 5});
    REQUIRE(equalList(Solution().reverseBetween(input, 2, 4), output));
}

