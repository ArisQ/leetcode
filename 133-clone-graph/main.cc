#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;


// Definition for a Node.
class Node {
public:
    int val;
    vector<Node *> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node *>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node *>();
    }
    Node(int _val, vector<Node *> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    Node *cloneGraph(Node *node) {
        if (node == nullptr)
            return node;
        vector<Node *> nodes(101, nullptr); //1<= val <= 100 // or HashSet
        Node *newFirst = new Node(node->val);
        nodes[node->val] = newFirst;
        dfs(nodes, node, newFirst);
        //vector<bool> accessed(101);
        //bfsSearch(accessed, node);
        //vector<bool> accessedNew(101);
        //bfsSearch(accessedNew, newFirst);
        return newFirst;
    }

    void dfsSearch(vector<bool> &access, Node *node) {
        if (access[node->val])
            return;
        access[node->val] = true;
        cout << node->val << " ";
        for (auto &n:node->neighbors) {
            cout << "(" << (n != nullptr ? n->val : -1) << "," << n << ") ";
        }
        cout << endl;
        for (auto &n:node->neighbors) {
            if (n != nullptr)
                dfsSearch(access, n);
        }
    }

    void dfs(vector<Node *> &nodes, Node *node, Node *newNode) {
        // cout<<node->val<<" "<<newNode->val<<endl;
        // cout<< __LINE__<<endl;
        int n = node->neighbors.size();
        newNode->neighbors.resize(n);
        for (int i = 0; i < n; ++i) {
            Node *nbi = node->neighbors[i];
            if (nodes[nbi->val] != nullptr) {
                newNode->neighbors[i] = nodes[nbi->val];
            } else {
                Node *p = new Node(nbi->val);
                nodes[nbi->val] = p;
                newNode->neighbors[i] = p;
                dfs(nodes, nbi, p);
            }
        }
    }
};

Node *makeGraph(initializer_list<initializer_list<int>> adjList) {
    int n = adjList.size();
    if (n == 0)
        return nullptr;
    vector<Node *> nodes(n);
    for (int i = 0; i < n; ++i)
        nodes[i] = new Node(i + 1);
    auto iter = adjList.begin();
    for (int i = 0; i < n; ++i, ++iter) {
        for (auto neighbor:*iter) {
            nodes[i]->neighbors.push_back(nodes[neighbor - 1]);
        }
    }

    // print
    vector<bool> accessed(n);
    Solution().dfsSearch(accessed, nodes[0]);
    return nodes[0];
}

bool isGraphCopyHelper(Node *left, Node *right, map<int, Node *> &rightNodeMap, map<int, bool> &accessed) {
    if (left == nullptr && right == nullptr)
        return true;
    if (left == nullptr || right == nullptr)
        return false;
    if (accessed[left->val])
        return true;
    if (left == right) //not copied
        return false;
    if (left->val != right->val)
        return false;
    int n = left->neighbors.size();
    if (n != right->neighbors.size())
        return false;
    if (rightNodeMap[right->val] == nullptr) {
        rightNodeMap[right->val] = right;
    } else {
        if (rightNodeMap[right->val] != right)
            return false;
    }
    accessed[left->val] = true;
    for (int i = 0; i < n; ++i) {
        if (!isGraphCopyHelper(left->neighbors[i], right->neighbors[i], rightNodeMap, accessed))
            return false;
    }
    return true;
}
bool isGraphCopy(Node *left, Node *right) {
    // assert graph val unique
    map<int, Node *> nodeMap; // 只检查右边
    map<int, bool> accessed;
    return isGraphCopyHelper(left, right, nodeMap, accessed);
}

TEST_CASE("Clone Graph") {
    auto input1 = makeGraph({{2, 4}, {1, 3}, {2, 4}, {1, 3}});
    REQUIRE(isGraphCopy(input1, Solution().cloneGraph(input1)));
    auto input2 = makeGraph({{}});
    REQUIRE(isGraphCopy(input2, Solution().cloneGraph(input2)));
    auto input3 = makeGraph({});
    REQUIRE(isGraphCopy(input3, Solution().cloneGraph(input3)));
    auto input4 = makeGraph({{2}, {1}});
    REQUIRE(isGraphCopy(input4, Solution().cloneGraph(input4)));
}
