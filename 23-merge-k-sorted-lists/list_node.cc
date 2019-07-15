#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <vector>
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

void freeListNode(ListNode *head) {
    while (head != nullptr) {
        auto p = head;
        head = head->next;
        delete p;
    }
}


bool equalListNode(const ListNode *l, const ListNode *r) {
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

void printListNode(const ListNode *head) {
    while (head != nullptr) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void printListNodeArray(vector<ListNode *> lists) {
    for(auto list in lists)
        printListNode(list);
}

void freeListNodeArray(vector<ListNode *> lists) {
    for(auto list in lists)
        freeList(list);
}


