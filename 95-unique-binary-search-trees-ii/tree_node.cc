#include "tree_node.h"
#include <queue>
#include <iostream>

using namespace std;

TreeNode *makeTree(std::initializer_list<TreeVal> values) {
    if (values.size() == 0 || values.begin()->isNull)
        return nullptr;
    auto iter = values.begin();
    auto root = new TreeNode(iter->val);
    queue<TreeNode *> nodes;
    nodes.push(root);
    ++iter;
    while (iter != values.end()) {
        auto node = nodes.front();
        nodes.pop();
        if (!iter->isNull) {
            node->left = new TreeNode(iter->val);
            nodes.push(node->left);
        }
        ++iter;
        if (iter == values.end())
            break;
        if (!iter->isNull) {
            node->right = new TreeNode(iter->val);
            nodes.push(node->right);
        }
        ++iter;
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

std::ostream &operator<<(std::ostream &os, const TreeNode *root) {
    vector<vector<TreeVal>> values;
    queue<const TreeNode *> nodeQueue;
    nodeQueue.push(root);
    bool allNull = false;
    while (!allNull) {
        allNull = true;
        vector<TreeVal> layerValues;
        size_t layerSize = nodeQueue.size();
        for (int i = 0; i < layerSize; ++i) {
            auto node = nodeQueue.front();
            nodeQueue.pop();
            if (node != nullptr) {
                layerValues.emplace_back(TreeVal(node->val));
                nodeQueue.push(node->left);
                nodeQueue.push(node->right);
                allNull = false;
            } else {
                layerValues.emplace_back(TreeVal(nullptr));
                nodeQueue.push(nullptr);
                nodeQueue.push(nullptr);
            }
        }
        values.push_back(layerValues);
    }
    int width = 2;
    int layer = values.size() - 1;
    int lead = 0, offset = 0;
    for (int i = 0; i < layer; ++i) {
        lead = (1 << (layer - 1 - i)) - 1;
        offset = 1 << (layer - i);
        for (int j = 0; j < lead; ++j) {
            os.width(width);
            os << " ";
        }
        for (auto &value:values[i]) {
            if (!value.isNull) {
                os.width(width);
                os << value.val;
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

bool equalTree(const TreeNode *a, const TreeNode *b) {
    if (a == nullptr && b == nullptr)
        return true;
    if (a == nullptr || b == nullptr)
        return false;
    if (a->val != b->val)
        return false;
    return equalTree(a->left, b->left) && equalTree(a->right, b->right);
}

int compareTree(const TreeNode *a, const TreeNode *b) {
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

bool lessTree(const TreeNode *a, const TreeNode *b) {
    return compareTree(a, b) == -1;
}
