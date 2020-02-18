#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
    int m, n;
public:
    void solve(vector<vector<char>> &board) {
        m = board.size();
        if (m == 0)
            return;
        n = board[0].size();
        if (n == 0)
            return;
        for (int i = 0; i < n; ++i) {
            if (board[0][i] == 'O') {
                board[0][i] = 'P';
                connect(board, 0, i);
            }
            if (board[m - 1][i] == 'O') {
                board[m - 1][i] = 'P';
                connect(board, m - 1, i);
            }
        }
        for (int i = 1; i < m - 1; ++i) {
            if (board[i][0] == 'O') {
                board[i][0] = 'P';
                connect(board, i, 0);
            }
            if (board[i][n - 1] == 'O') {
                board[i][n - 1] = 'P';
                connect(board, i, n - 1);
            }
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'P')
                    board[i][j] = 'O';
                else
                    board[i][j] = 'X';
            }
        }
    }
    void connect(vector<vector<char>> &board, int i, int j) {
        //up down left right
        //i  j
        if (i > 0 && board[i - 1][j] == 'O') {
            board[i - 1][j] = 'P';
            connect(board, i - 1, j);
        }
        if (i < m - 1 && board[i + 1][j] == 'O') {
            board[i + 1][j] = 'P';
            connect(board, i + 1, j);
        }
        if (j > 0 && board[i][j - 1] == 'O') {
            board[i][j - 1] = 'P';
            connect(board, i, j - 1);
        }
        if (j < n - 1 && board[i][j + 1] == 'O') {
            board[i][j + 1] = 'P';
            connect(board, i, j + 1);
        }
    }
};

TEST_CASE("Surrounded Regions") {
    vector<vector<char>> input{
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'}
    };
    vector<vector<char>> output{
        {'X', 'X', 'X', 'X'},
        {'X', 'X', 'X', 'X'},
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'X', 'X'}
    };
    Solution().solve(input);
    REQUIRE(input == output);
}

TEST_CASE("Surrounded Regions - Wrong Answer") {
    vector<vector<char>> input{{'O', 'O', 'O'}, {'O', 'O', 'O'}, {'O', 'O', 'O'}};
    vector<vector<char>> output{{'O', 'O', 'O'}, {'O', 'O', 'O'}, {'O', 'O', 'O'}};
    Solution().solve(input);
    REQUIRE(input == output);
}
