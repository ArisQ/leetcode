#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "list_node.h"

using namespace std;

class Solution {
public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        ListNode dummy = ListNode(0);
        ListNode *p = &dummy;
        ListNode *q, *r;
        vector<ListNode *> stack;
        p->next = head;
        q = p->next;
        while (true) {
            // push into stack
            for (int i = 0; i < k; ++i) {
                if (q) {
                    stack.push_back(q);
                    q = q->next;
                } else {
                    break;
                }
            }
            if (stack.size() < k)
                break;
            // pop out from stack
            for (int i = 0; i < k; ++i) {
                r = stack.back();
                stack.pop_back();
                p->next = r;
                p = r;
            }
            p->next = q;
        }
        return dummy.next;
    }
};

TEST_CASE("Reverse Nodes in k-Group - k=2") {
    auto input = makeList({1, 2, 3, 4, 5});
    auto output = makeList({2, 1, 4, 3, 5});
    cout << input << endl;
    cout << output << endl;
    auto answer = Solution().reverseKGroup(input, 2);
    cout << answer << endl;
    REQUIRE(equalList(answer, output));
    freeList(output);
    freeList(answer);
}

TEST_CASE("Reverse Nodes in k-Group - k=3") {
    auto input = makeList({1, 2, 3, 4, 5});
    auto output = makeList({3, 2, 1, 4, 5});
    cout << input << endl;
    cout << output << endl;
    auto answer = Solution().reverseKGroup(input, 3);
    cout << answer << endl;
    REQUIRE(equalList(answer, output));
    freeList(output);
    freeList(answer);
}
