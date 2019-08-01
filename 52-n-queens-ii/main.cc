#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    int totalNQueens(int n) {
        int result = 0;
        vector<bool> column_occupied(n, false);
        vector<vector<int>> under_attack(n, vector<int>(n, 0));
        pickAtRow(n, 0, result, column_occupied, under_attack);
        return result;
    }

    void pickAtRow(int n, int row, int &result,
                   vector<bool> &column_occupied,
                   vector<vector<int>> &under_attack
    ) {
        if (row == n) {
            ++result;
            return;
        }
        for (int i = 0; i < n; ++i) {
            if (column_occupied[i] || under_attack[row][i] != 0)
                continue;
            column_occupied[i] = true;
            for (int j = 1; i - j >= 0 && row + j < n; ++j)
                ++under_attack[row + j][i - j];
            for (int j = 1; i + j < n && row + j < n; ++j)
                ++under_attack[row + j][i + j];
            pickAtRow(n, row + 1, result, column_occupied, under_attack);
            column_occupied[i] = false;
            for (int j = 1; i - j >= 0 && row + j < n; ++j)
                --under_attack[row + j][i - j];
            for (int j = 1; i + j < n && row + j < n; ++j)
                --under_attack[row + j][i + j];
        }
    }
};

TEST_CASE("N-Queens II") {
    REQUIRE(Solution().totalNQueens(4) == 2);
    for (int i = 1; i < 100; ++i)
        cout << i << " " << Solution().totalNQueens(i) << endl;
}
