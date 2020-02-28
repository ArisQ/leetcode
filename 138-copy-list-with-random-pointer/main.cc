#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <unordered_map>

using namespace std;

class Node {
public:
    int val;
    Node *next;
    Node *random;

    explicit Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};
ostream &operator<<(ostream &os, const Node *node) {
    if (node == nullptr) {
        os << "nullptr" << endl;
    } else {
        os << "[" << static_cast<const void *>(node) << "] ";
        os << setw(2) << node->val << ", ";
        os << setw(9) << static_cast<void *>(node->next) << ", ";
        os << setw(9) << static_cast<void *>(node->random) << endl;
        os << node->next;
    }
    return os;
}
struct NodeIndex {
    int val;
    bool isNull;
    NodeIndex(const void *) : val(-1), isNull(true) {}
    NodeIndex(int val) : val(val), isNull(false) {}
};

Node *make_list(const initializer_list<pair<int, NodeIndex>> list) {
    int n = list.size();
    vector<Node *> nodes(n + 1); // 末尾为nullptr
    int i = 0;
    for (auto iter = list.begin(); iter != list.end(); ++iter, ++i) {
        nodes[i] = new Node(iter->first);
    }
    i = 0;
    for (auto iter = list.begin(); iter != list.end(); ++iter, ++i) {
        nodes[i]->next = nodes[i + 1]; //nodes[n]=nullptr
        if (!iter->second.isNull) {
            nodes[i]->random = nodes[iter->second.val];
        }
    }
    return nodes[0];
}
bool isListCopy(const Node *l, const Node *r) {
    const Node *p = l, *q = r;
    unordered_map<const Node *, const Node *> map;
    while (p != nullptr && q != nullptr) {
        if (p->val != q->val) {
            return false;
        }
        map[p] = q;
        p = p->next;
        q = q->next;
    }
    if (p != nullptr || q != nullptr) {
        return false;
    }
    p = l;
    q = r;
    while (p != nullptr) {
        assert(q != nullptr);
        if (q->next != map[p->next]) {
            return false;
        }
        if (p->random == nullptr || q->random == nullptr) {
            if (p->random != nullptr || q->random != nullptr) {
                return false;
            }
        } else {
            if (q->random != map[p->random]) {
                return false;
            }
        }
        p = p->next;
        q = q->next;
    }
    return true;
}

class Solution {
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/
public:
    Node *copyRandomList(Node *head) {
        unordered_map<Node *, Node *> node_map;
        Node *p = head;
        while (p != nullptr) {
            node_map[p] = new Node(p->val);
            p = p->next;
        }
        p = head;
        Node *q;
        while (p != nullptr) {
            q = node_map[p];
            q->next = node_map[p->next];
            if (p->random != nullptr)
                q->random = node_map[p->random];
            p = p->next;
        }
        return node_map[head];
    }
};

TEST_CASE("Copy List with Random Pointer") {
    auto list1 = make_list({{7, nullptr}, {13, 0}, {11, 4}, {10, 2}, {1, 0}});
    auto list2 = make_list({{1, 1}, {2, 1}});
    auto list3 = make_list({{3, nullptr}, {3, 0}, {3, nullptr}});
    auto list4 = make_list({});
    cout << list1 << endl;
    cout << Solution().copyRandomList(list1) << endl;
    REQUIRE(isListCopy(Solution().copyRandomList(list1), list1));
    REQUIRE(isListCopy(Solution().copyRandomList(list2), list2));
    REQUIRE(isListCopy(Solution().copyRandomList(list3), list3));
    REQUIRE(isListCopy(Solution().copyRandomList(list4), list4));
}
