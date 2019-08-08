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
class NodePool {
    struct PoolNode {
        T node;
        PoolNode *next;
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
        tail = &pool[0];
    }

    T *getNode() {
        if (head!= nullptr &&tail == head)
            return nullptr;
        auto &node = tail->node;
        if(head== nullptr)
            head=tail;
        tail = tail->next;
        return &node;
    }

    friend ostream &operator<<(ostream &os, const NodePool<T> &list) {
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
    NodePool<ListNode> pool(10);
    cout << pool << endl;
    ListNode *node = pool.getNode();
    if (node == nullptr) {
        cout << "get node error" << endl;
        return -1;
    }
    cout << *node << endl;
    return 0;
}

