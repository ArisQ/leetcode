#ifndef TREE_NODE_WITH_NEXT_H
#define TREE_NODE_WITH_NEXT_H

#include <initializer_list>
#include <ostream>

// Definition for a binary tree node with next pointer.
class TreeNodeWithNext {
public:
    int val;
    TreeNodeWithNext *left;
    TreeNodeWithNext *right;
    TreeNodeWithNext *next;

    explicit TreeNodeWithNext(int val,
                              TreeNodeWithNext *left = nullptr,
                              TreeNodeWithNext *right = nullptr,
                              TreeNodeWithNext *next = nullptr)
        : val(val), left(left), right(right), next(right) {}
};

struct TreeVal {
    int val;
    bool isNull;

    TreeVal(void *) : val(-1), isNull(true) {}

    TreeVal(int val) : val(val), isNull(false) {}
};

TreeNodeWithNext *makeTreeWithNext(std::initializer_list<TreeVal> values, bool fillNext = false);

bool equalTreeWithNext(const TreeNodeWithNext *a, const TreeNodeWithNext *b);
bool lessTreeWithNext(const TreeNodeWithNext *a, const TreeNodeWithNext *b);

std::ostream &operator<<(std::ostream &os, const TreeNodeWithNext *root);

struct TreeWithNext {
    TreeNodeWithNext *root;

    TreeWithNext(TreeNodeWithNext *root) : root(root) {}

    friend bool operator<(const TreeWithNext &a, const TreeWithNext &b) {
        return lessTreeWithNext(a.root, b.root);
    }

    friend bool operator==(const TreeWithNext &a, const TreeWithNext &b) {
        return equalTreeWithNext(a.root, b.root);
    }

    friend std::ostream &operator<<(std::ostream &os, const TreeWithNext *tree) {
        os << tree->root;
        return os;
    }
};

#endif /* ifndef TREE_NODE_WITH_NEXT_H */
