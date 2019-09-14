#include "tree_node_with_next.h"
#include <queue>
#include <iostream>

using namespace std;

TreeNodeWithNext *makeTreeWithNext(std::initializer_list<TreeVal> values, bool fillNext) {
    if (values.size() == 0 || values.begin()->isNull)
        return nullptr;
    auto iter = values.begin();
    auto root = new TreeNodeWithNext(iter->val);
    queue<TreeNodeWithNext *> nodes;
    nodes.push(root);
    if (fillNext) {
        nodes.push(nullptr); // 层结束标志
    }
    TreeNodeWithNext dummy(0), *previous = &dummy;
    ++iter;
    while (iter != values.end()) {
        auto node = nodes.front();
        nodes.pop();
        if (fillNext) {
            if (node == nullptr) { // layer end marker
                previous = &dummy;
                nodes.push(nullptr);
                continue;
            } else {
                previous->next = node;
                previous = node;
            }
        }

        if (!iter->isNull) {
            node->left = new TreeNodeWithNext(iter->val);
            nodes.push(node->left);
        }
        ++iter;
        if (iter == values.end())
            break;
        if (!iter->isNull) {
            node->right = new TreeNodeWithNext(iter->val);
            nodes.push(node->right);
        }
        ++iter;
    }
    if (fillNext) {
        while (!nodes.empty()) {
            auto node = nodes.front();
            nodes.pop();
            if (node == nullptr) { // layer end marker
                previous = &dummy;
                if (!nodes.empty()) {
                    nodes.push(nullptr);
                }
                continue;
            } else {
                previous->next = node;
                previous = node;
            }
        }
    }
    return root;
}

ostream &operator<<(ostream &os, const TreeVal val) {
    if (val.isNull)
        os << "NULL";
    else
        os << val.val;
    return os;
}

std::ostream &operator<<(std::ostream &os, const TreeNodeWithNext *root) {
    vector<vector<const TreeNodeWithNext *>> nodeTriangle; // node 三角形
    queue<const TreeNodeWithNext *> nodeQueue;
    nodeQueue.push(root);
    bool allNull = false;
    while (!allNull) {
        allNull = true;
        vector<const TreeNodeWithNext *> layerValues;
        size_t layerSize = nodeQueue.size();
        for (int i = 0; i < layerSize; ++i) {
            auto node = nodeQueue.front();
            nodeQueue.pop();
            if (node != nullptr) {
                layerValues.emplace_back(node);
                nodeQueue.push(node->left);
                nodeQueue.push(node->right);
                allNull = false;
            } else {
                layerValues.emplace_back(nullptr);
                nodeQueue.push(nullptr);
                nodeQueue.push(nullptr);
            }
        }
        nodeTriangle.push_back(layerValues);
    }
    int width = 3;
    int layer = nodeTriangle.size() - 1;
    int lead = 0, offset = 0;
    for (int i = 0; i < layer; ++i) {
        lead = (1 << (layer - 1 - i)) - 1;
        offset = 1 << (layer - i);
        for (int j = 0; j < lead; ++j) {
            os.width(width);
            os << " ";
        }
        for (auto &node:nodeTriangle[i]) {
            if (node != nullptr) {
                os.width(width);
                os << node->val << "(" << (node->next ? node->next->val : -1) << ")";
            } else {
                os.width(width);
                os << 'N';
            }
            for (int j = 0; j < offset - 1; ++j) {
                os.width(width);
                os << " ";
            }
        }
        os << endl;
    }
    return os;
}

bool equalTreeWithNext(const TreeNodeWithNext *a, const TreeNodeWithNext *b) {
    if (a == nullptr && b == nullptr)
        return true;
    if (a == nullptr || b == nullptr)
        return false;
    if (a->val != b->val)
        return false;
    if (!((a->next == nullptr && b->next == nullptr)
        || (a->next != nullptr && b->next != nullptr && a->next->val == b->next->val)))
        return false;// 只能保证next的值相等，不能判断节点相等
    return equalTreeWithNext(a->left, b->left) && equalTreeWithNext(a->right, b->right);
}

int compareTree(const TreeNodeWithNext *a, const TreeNodeWithNext *b) {
    // a<b   -1
    // a==b  0
    // a>b   1
    if (a == nullptr && b == nullptr)
        return 0;
    if (a == nullptr)
        return -1; //b!=null
    if (b == nullptr)
        return 1; //a!==null
    if (a->val < b->val)
        return -1;
    if (a->val > b->val)
        return 1;
    int left = compareTree(a->left, b->left);
    if (left == 0)
        return compareTree(a->right, b->right);
    return left;
}

bool lessTree(const TreeNodeWithNext *a, const TreeNodeWithNext *b) {
    return compareTree(a, b) == -1;
}
