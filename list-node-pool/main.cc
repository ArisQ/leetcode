#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
};

ostream &operator<<(ostream &os, const ListNode &node) {
    os << node.val << " " << node.next;
    return os;
}

template<class T>
class NodePoolList {
    struct PoolNode {
        T node;
        PoolNode *next;
    };
public:
    explicit NodePoolList(size_t n) :
        pool_size(n),
        pool(vector<PoolNode>(n)) {
        for (size_t i = 0; i < n - 1; ++i) {
            pool[i].next = &pool[i + 1];
        }
        pool[n - 1].next = &pool[0];
        tail = &pool[0];
    }

    T *getNode() {
        if (tail == head)
            return nullptr;
        auto &node = tail->node;
        tail = tail->next;
        return &node;
    }

    friend ostream &operator<<(ostream &os, const NodePoolList<T> &list) {
        os << "NodePool:" << endl;
        for (auto &n:list.pool) {
            os << "Node " << &n << " ->" << n.next << " {" << n.node << "}" << endl;
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
    NodePoolList<ListNode> poolList(10);
    cout << poolList << endl;
    ListNode *node = poolList.getNode();
    if (node == nullptr) {
        cout << "get node error" << endl;
        return -1;
    }
    cout << *node << endl;
    return 0;
}

