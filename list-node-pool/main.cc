#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
};

ostream &operator<<(ostream &os, const ListNode &node) {
    os << "<" << node.val << " " << node.next << "> ";
    return os;
}

ostream &operator<<(ostream &os, const ListNode *node) {
    const ListNode *p = node;
    while (p != nullptr) {
        cout << *p;
        p = p->next;
    }
    return os;
}

template<class T>
class NodePool {
    struct PoolNode {
        T node;
        PoolNode *previous;
        PoolNode *next;
        int index;
    };
public:
    explicit NodePool(size_t n) :
        pool_size(n),
        pool(vector<PoolNode>(n)),
        head(nullptr) {
        for (size_t i = 0; i < n - 1; ++i) {
            pool[i].next = &pool[i + 1];
        }
        pool[n - 1].next = &pool[0];
        for (size_t i = 1; i < n; ++i) {
            pool[i].previous = &pool[i - 1];
        }
        pool[0].previous = &pool[n - 1];
        tail = &pool[0];
        for (size_t i = 0; i < n; ++i)
            pool[i].index = i;

        cout << *this;
        for (auto &node:pool) {
            cout << &node << " " << &(node.node) << endl;
        }
    }

    T *getNode() {
        if (head != nullptr && tail == head)
            return nullptr; //full
        auto &node = tail->node;
        if (head == nullptr)
            head = tail;
        tail = tail->next;
        return &node;
    }

    void freeNode(T *node) {
        PoolNode *poolNode = (PoolNode *) node; //PoolNodeForNode(node)
        // check
        if (head == poolNode) {
            head = head->next;
            if (head == tail)
                head = nullptr;
        }
        poolNode->previous->next = poolNode->next;
        poolNode->next->previous = poolNode->previous;
        poolNode->next = tail->next;
        tail->next->previous = poolNode;
        poolNode->previous = tail;
        tail->next = poolNode;
    }

    //resize

    friend ostream &operator<<(ostream &os, const NodePool<T> &list) {
        os << "NodePool:" << endl;
        for (auto &n:list.pool) {
            os << "Node " << &n << "(" << n.index << ") "
               << " <-" << n.previous << "(" << n.previous->index << ") "
               << " ->" << n.next << "(" << n.next->index << ") "
               << " {" << n.node << "}";
            if (&n == list.head)
                os << " HEAD";
            if (&n == list.tail)
                os << " TAIL";
            os << endl;
        }
        return os;
    }

private:
    size_t pool_size;
    vector<PoolNode> pool;
    PoolNode *head;
    PoolNode *tail;
};


int main() {
    NodePool<ListNode> pool(10);
    ListNode *node = pool.getNode();
    if (node == nullptr) {
        cout << "get node error" << endl;
        return -1;
    }
    node->val = 1;
    cout << *node << endl;
    cout << pool << endl;
    pool.freeNode(node);
    cout << *node << endl;
    cout << pool << endl;

    ListNode *head = nullptr;
    int count = 0;
    for (int c = 0; c < 100; ++c) {
        int x = rand() % 100;
        if (x > 90 && count > 0) {
            cout << "deleting" << endl;
            int i = x % count;
            ListNode *p = head;
            if (i == 0) {
                head = head->next;
                pool.freeNode(p);
            } else {
                while (i-- > 1)
                    p = p->next;
                ListNode *q = p->next;
                p->next = q->next;
                pool.freeNode(q);
            }
            --count;
        } else {
            cout << "adding" << endl;
            ListNode *p, *q;
            p = pool.getNode();
            if (p == nullptr)
                continue;
            p->val = x;
            p->next = nullptr;
            if (head == nullptr) {
                head = p;
            } else {
                q = head;
                while (q->next != nullptr) {
                    cout << q << endl;
                    cout << pool << endl;
                    q = q->next;
                }
                q->next = p;
            }
            ++count;
        }
        cout << pool;
        cout << head << endl;
    }
    return 0;
}

