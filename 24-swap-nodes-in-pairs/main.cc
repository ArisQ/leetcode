#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "list_node.h"

using namespace std;

class Solution {
public:
    ListNode *swapPairs(ListNode *head) {
        auto dummy = ListNode(0);
        auto p = &dummy;
        p->next = head;
        while (p->next && p->next->next) {
            auto q = p->next;
            p->next = q->next;
            q->next = p->next->next;
            p->next->next = q;
            p = p->next->next;
        }
        return dummy.next;
    }
};

TEST_CASE("Swap Nodes in Pairs - 1") {
    auto input = makeList({1, 2, 3, 4});
    auto output = makeList({2, 1, 4, 3});
    cout << input << endl;
    cout << output << endl;
    auto answer = Solution().swapPairs(input);
    cout << answer << endl;
    REQUIRE(equalList(answer, output));
    freeList(output);
    freeList(answer);
}

TEST_CASE("Swap Nodes in Pairs - 2") {
    auto input = makeList({4, 8});
    auto output = makeList({8, 4});
    cout << input << endl;
    cout << output << endl;
    auto answer = Solution().swapPairs(input);
    cout << answer << endl;
    REQUIRE(equalList(answer, output));
    freeList(output);
    freeList(answer);
}

