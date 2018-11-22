#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <vector>

using namespace std;

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        if (l1 == NULL)
            return l2;
        if (l2 == NULL)
            return l1;
        if (l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        } else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};

class Solution2 {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode h(0);
        ListNode *p = &h;
        while (l1 != NULL && l2 != NULL) {
            if (l1->val < l2->val) {
                p->next = l1;
                p = l1;
                l1 = l1->next;
            } else {
                p->next = l2;
                p = l2;
                l2 = l2->next;
            }
        }
        if (l1 == NULL)
            p->next = l2;
        else
            p->next = l1;
        return h.next;
    }
};

ListNode *makeListNode(const vector<int> values) {
    ListNode *head = NULL;
    for (auto iter = values.crbegin(); iter != values.crend(); ++iter) {
        auto p = new ListNode(*iter);
        p->next = head;
        head = p;
    }
    return head;
}

void freeListNode(ListNode *head) {
    while (head != NULL) {
        auto p = head;
        head = head->next;
        delete p;
    }
}

bool equalListNode(const ListNode *l, const ListNode *r) {
    while (l != NULL && r != NULL) {
        if (l->val != r->val)
            return false;
        l = l->next;
        r = r->next;
    }
    if (l != NULL || r != NULL)
        return false;
    return true;
}

void printListNode(const ListNode *head) {
    while (head != NULL) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

TEST_CASE("Merge Two Sorted Lists - Solution") {
    auto input1 = makeListNode({1, 2, 4});
    auto input2 = makeListNode({1, 3, 4});
    auto output = makeListNode({1, 1, 2, 3, 4, 4});
    printListNode(input1);
    printListNode(input2);
    printListNode(output);
    auto answer = Solution().mergeTwoLists(input1, input2);
    printListNode(answer);
    REQUIRE(equalListNode(answer, output) == true);
    freeListNode(output);
    freeListNode(answer);
}

TEST_CASE("Merge Two Sorted Lists - Solution2") {
    auto input1 = makeListNode({1, 2, 4});
    auto input2 = makeListNode({1, 3, 4});
    auto output = makeListNode({1, 1, 2, 3, 4, 4});
    printListNode(input1);
    printListNode(input2);
    printListNode(output);
    auto answer = Solution2().mergeTwoLists(input1, input2);
    printListNode(answer);
    REQUIRE(equalListNode(answer, output) == true);
    freeListNode(output);
    freeListNode(answer);
}
