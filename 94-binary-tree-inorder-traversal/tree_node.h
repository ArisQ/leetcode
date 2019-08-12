#ifndef TREE_NODE_H
#define TREE_NODE_H

// Definition for a binary tree node.
class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

#endif /* ifndef TREE_NODE_H */
