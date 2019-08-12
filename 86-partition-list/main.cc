#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "list_node.h"

using namespace std;

class Solution {
public:
    ListNode *partition(ListNode *head, int x) {
        ListNode lessHead(0), greatEqualHead(0);
        ListNode *lessEnd = &lessHead, *greatEqualEnd = &greatEqualHead;
        while (head != nullptr) {
            if (head->val < x) {
                lessEnd->next = head;
                lessEnd = head;
            } else {
                greatEqualEnd->next = head;
                greatEqualEnd = head;
            }
            head = head->next;
        }
        lessEnd->next = greatEqualHead.next;
        greatEqualEnd->next = nullptr;
        return lessHead.next;
    }
};

TEST_CASE("Partition List") {
    ListNode *input = makeList({1, 4, 3, 2, 5, 2});
    ListNode *output = makeList({1, 2, 2, 4, 3, 5});
    cout << input << endl;
    cout << output << endl;
    REQUIRE(equalList(Solution().partition(input, 3), output));
}

TEST_CASE("Partition List - Wrong Answer 1") {
    ListNode *input = makeList({3, 1, 2});
    ListNode *output = makeList({1, 2, 3});
    cout << input << endl;
    cout << output << endl;
    REQUIRE(equalList(Solution().partition(input, 3), output));
}
