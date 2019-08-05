#define CATCH_CONFIG_MAIN

#include <queue>
#include <catch.hpp>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
        cout.width(3);
        os << element;
    }
    os << endl;
    return os;
}

struct Node {
    int i;
    int j;
    int sum;
};

ostream &operator<<(ostream &os, const Node &node) {
    os << "node<" << node.i << "," << node.j << "," << node.sum << ">";
    return os;
}

template<typename T>
void print_queue(T q) {
    std::cout << "[ ";
    while (!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << "] ";
    std::cout << '\n';
}

class Solution {
public:
    int minPathSum(vector<vector<int>> &grid) {
        //A*
        if (grid.empty())
            return 0;
        auto nodeCompare = [](const Node &n1, const Node &n2) {
            return n1.i + n1.j + n1.sum > n2.i + n2.j + n2.sum;
        };
        priority_queue<Node, vector<Node>, decltype(nodeCompare)> nodeQueue(nodeCompare);
        int m = grid.size();
        int n = grid[0].size();
        nodeQueue.push({m - 1, n - 1, grid[m - 1][n - 1]});
        while (!nodeQueue.empty()) {
            print_queue(nodeQueue);
            auto node = nodeQueue.top();//copy, 如果引用，则在push后可能被覆盖
            nodeQueue.pop();
            if (node.i == 0 && node.j == 0)
                return node.sum;
            if (node.i > 0) {
                nodeQueue.push({node.i - 1, node.j, node.sum + grid[node.i - 1][node.j]});
            }
            if (node.j > 0) {
                nodeQueue.push({node.i, node.j - 1, node.sum + grid[node.i][node.j - 1]});
            }
        }
        return 0;
    }
};

class Solution2 {
public:
    int minPathSum(vector<vector<int>> &grid) {
        if (grid.empty())
            return 0;
        int m = grid.size();
        int n = grid[0].size();
        for (int i = m - 2; i >= 0; --i)
            grid[i][n - 1] += grid[i + 1][n - 1];
        for (int i = n - 2; i >= 0; --i)
            grid[m - 1][i] += grid[m - 1][i + 1];
        for (int i = m - 2; i >= 0; --i)
            for (int j = n - 2; j >= 0; --j)
                grid[i][j] += min(grid[i + 1][j], grid[i][j + 1]);
        return grid[0][0];
    }
};

TEST_CASE("Minimum Path Sum") {
    vector<vector<int>> input{
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}
    };
    REQUIRE(Solution2().minPathSum(input) == 7);
}

TEST_CASE("Minimum Path Sum - Time Limit Exceeded") {
    vector<vector<int>> input{
        {4, 8, 2, 9, 5, 8, 5, 0, 8, 4, 7, 4, 0, 4, 2},
        {4, 9, 5, 4, 9, 3, 4, 8, 6, 3, 7, 3, 7, 9, 9},
        {4, 4, 7, 6, 5, 4, 6, 2, 4, 6, 6, 2, 0, 7, 8},
        {4, 3, 7, 9, 0, 6, 5, 4, 6, 1, 0, 4, 6, 7, 5},
        {5, 3, 9, 4, 1, 6, 1, 7, 9, 5, 5, 7, 9, 5, 6},
        {8, 9, 0, 5, 1, 0, 4, 6, 6, 2, 7, 6, 6, 3, 5},
        {2, 0, 0, 3, 6, 1, 2, 7, 0, 1, 5, 5, 0, 4, 2},
        {7, 2, 4, 7, 0, 7, 9, 6, 3, 7, 8, 2, 4, 7, 7},
        {1, 1, 7, 2, 4, 5, 3, 6, 5, 6, 9, 0, 3, 2, 4},
        {8, 9, 9, 2, 8, 1, 9, 7, 9, 4, 4, 7, 6, 0, 6},
        {3, 2, 7, 2, 6, 2, 9, 1, 0, 4, 7, 2, 4, 1, 4},
        {1, 1, 5, 2, 3, 3, 3, 4, 0, 2, 8, 6, 1, 6, 9},
        {8, 9, 1, 5, 3, 7, 9, 2, 8, 2, 7, 8, 6, 3, 1},
        {2, 4, 2, 7, 6, 7, 0, 1, 1, 2, 5, 1, 8, 7, 7},
        {7, 7, 8, 0, 2, 1, 9, 4, 5, 0, 8, 2, 0, 4, 6},
        {1, 6, 2, 5, 3, 1, 2, 3, 2, 5, 7, 8, 6, 5, 7}
    };
    REQUIRE(Solution2().minPathSum(input) == 92);
}

TEST_CASE("Minimum Path Sum - Runtime Error") {
    vector<vector<int>> input{
        {1, 2},
        {5, 6},
        {1, 1}
    };
    REQUIRE(Solution2().minPathSum(input) == 8);
}
