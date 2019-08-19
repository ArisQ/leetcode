#include <vector>
#include <iostream>
#include "list_node.h"

using namespace std;

ListNode *makeList(vector<int> values) {
    ListNode *head = nullptr;
    for (auto iter = values.crbegin(); iter != values.crend(); ++iter) {
        auto p = new ListNode(*iter);
        p->next = head;
        head = p;
    }
    return head;
}

ListNode *makeList(initializer_list<int> values) {
    ListNode *head = nullptr, *p = nullptr;
    if (values.size() == 0)
        return head;
    auto iter = values.begin();
    p = new ListNode(*iter);
    head = p;
    ++iter;
    for (; iter != values.end(); ++iter) {
        auto q = new ListNode(*iter);
        p->next = q;
        p = q;
    }
    return head;
}

void freeList(ListNode *head) {
    while (head != nullptr) {
        auto p = head;
        head = head->next;
        delete p;
    }
}

bool equalList(const ListNode *l, const ListNode *r) {
    while (l != nullptr && r != nullptr) {
        if (l->val != r->val)
            return false;
        l = l->next;
        r = r->next;
    }
    if (l != nullptr || r != nullptr)
        return false;
    return true;
}

ostream &operator<<(ostream &os, const ListNode *head) {
    while (head != nullptr) {
        os << head->val << " ";
        head = head->next;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, std::vector<ListNode *> &lists) {
    cout << "list<" << lists.size() << ">:";
    for (auto list : lists)
        cout << endl << list;
    return os;
}

void freeListArray(vector<ListNode *> lists) {
    for (auto list : lists)
        freeList(list);
}

