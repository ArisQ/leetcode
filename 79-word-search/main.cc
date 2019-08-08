#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
private:
    int m, n;
    vector<vector<bool>> used;
public:
    bool exist(vector<vector<char>> &board, string word) {
        if (board.empty())
            return true;
        if (board.empty() || board[0].empty())
            return false;
        m = board.size();
        n = board[0].size();
        used = vector<vector<bool>>(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == word[0]) {
                    used[i][j] = true;
                    if (find(board, word, i, j, 1))
                        return true;
                    used[i][j] = false;
                }
            }
        return false;
    }

    bool find(const vector<vector<char>> &board,
              const string &word,
              int i, int j, int index) {
        if (index == word.size())
            return true;
        if (i > 0 && board[i - 1][j] == word[index] && !used[i - 1][j]) {
            used[i - 1][j] = true;
            if (find(board, word, i - 1, j, index + 1))
                return true;
            used[i - 1][j] = false;
        }
        if (i < m - 1 && board[i + 1][j] == word[index] && !used[i + 1][j]) {
            used[i + 1][j] = true;
            if (find(board, word, i + 1, j, index + 1))
                return true;
            used[i + 1][j] = false;
        }
        if (j > 0 && board[i][j - 1] == word[index] && !used[i][j - 1]) {
            used[i][j - 1] = true;
            if (find(board, word, i, j - 1, index + 1))
                return true;
            used[i][j - 1] = false;
        }
        if (j < n - 1 && board[i][j + 1] == word[index] && !used[i][j + 1]) {
            used[i][j + 1] = true;
            if (find(board, word, i, j + 1, index + 1))
                return true;
            used[i][j + 1] = false;
        }
        return false;
    }
};

TEST_CASE("Word Search") {
    vector<vector<char>> board{
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };
    REQUIRE(Solution().exist(board, "ABCCED") == true);
    REQUIRE(Solution().exist(board, "SEE") == true);
    REQUIRE(Solution().exist(board, "ABCB") == false);
}

