#define CATCH_CONFIG_MAIN

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

ostream &operator<<(ostream &os, const vector<string> &array) {
    for (auto element:array) {
        os << element << endl;
    }
    os << endl;
    return os;
}

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        vector<string> board(n, string(n, '.'));
        vector<bool> column_occupied(n, false);
        vector<vector<int>> under_attack(n, vector<int>(n, 0));
        pickAtRow(n, result, board, column_occupied, under_attack, 0);
        return result;
    }

    void pickAtRow(int n,
                   vector<vector<string>> &result,
                   vector<string> &board,
                   vector<bool> &column_occupied,
                   vector<vector<int>> &under_attack,
                   int row
    ) {
        if (row == n) {
            result.push_back(board);
            return;
        }
        for (int i = 0; i < n; ++i) {
            if (column_occupied[i] || under_attack[row][i] != 0)
                continue;
            board[row][i] = 'Q';
            column_occupied[i] = true;
            for (int j = 1; i - j >= 0 && row + j < n; ++j)
                ++under_attack[row + j][i - j];
            for (int j = 1; i + j < n && row + j < n; ++j)
                ++under_attack[row + j][i + j];
            pickAtRow(n, result, board, column_occupied, under_attack, row + 1);
            board[row][i] = '.';
            column_occupied[i] = false;
            for (int j = 1; i - j >= 0 && row + j < n; ++j)
                --under_attack[row + j][i - j];
            for (int j = 1; i + j < n && row + j < n; ++j)
                --under_attack[row + j][i + j];
        }
    }
};

TEST_CASE("N-Queens - 4") {
    vector<vector<string>> result =
        {{
             ".Q..",  // Solution 1
             "...Q",
             "Q...",
             "..Q."
         },
         {
             "..Q.",  // Solution 2
             "Q...",
             "...Q",
             ".Q.."
         }};
    REQUIRE(Solution().solveNQueens(4) == result);
    cout << Solution().solveNQueens(8);
}
