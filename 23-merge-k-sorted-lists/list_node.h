#ifndef LIST_NODE_H
#define LIST_NODE_H

//Definition for singly-linked list.
class ListNode {
public:
    int val;
    ListNode *next;

    explicit ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *makeList(std::vector<int> values);
void freeList(ListNode *head);

bool equalListNode(const ListNode *l, const ListNode *r);
void printListNode(const ListNode *head);

void printListArray(std::vector<ListNode *> lists);
void freeListArray(std::vector<ListNode *> lists);

#endif /* ifndef LIST_NODE_H */
