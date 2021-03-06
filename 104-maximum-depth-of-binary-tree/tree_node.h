#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <initializer_list>
#include <ostream>

// Definition for a binary tree node.
class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct TreeVal {
    int val;
    bool isNull;

    TreeVal(void *) : val(-1), isNull(true) {}

    TreeVal(int val) : val(val), isNull(false) {}
};

TreeNode *makeTree(std::initializer_list<TreeVal> values);

bool equalTree(const TreeNode *a, const TreeNode *b);
bool lessTree(const TreeNode *a, const TreeNode *b);

std::ostream &operator<<(std::ostream &os, const TreeNode *root);

struct Tree {
    TreeNode *root;

    Tree(TreeNode *root) : root(root) {}

    friend bool operator<(const Tree &a, const Tree &b) {
        return lessTree(a.root, b.root);
    }

    friend bool operator==(const Tree &a, const Tree &b) {
        return equalTree(a.root, b.root);
    }

    friend std::ostream &operator<<(std::ostream &os, const Tree *tree) {
        os << tree->root;
        return os;
    }
};

#endif /* ifndef TREE_NODE_H */
