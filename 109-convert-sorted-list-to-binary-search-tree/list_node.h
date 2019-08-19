#ifndef LIST_NODE_H
#define LIST_NODE_H

#include <vector>
#include <initializer_list>

//Definition for singly-linked list.
class ListNode {
public:
    int val;
    ListNode *next;

    explicit ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *makeList(std::vector<int> values);

ListNode *makeList(std::initializer_list<int> values);

void freeList(ListNode *head);

bool equalList(const ListNode *l, const ListNode *r);

std::ostream &operator<<(std::ostream &os, const ListNode * head);

std::ostream &operator<<(std::ostream &os, std::vector<ListNode *> &lists);

void freeListArray(std::vector<ListNode *> lists);

#endif /* ifndef LIST_NODE_H */
