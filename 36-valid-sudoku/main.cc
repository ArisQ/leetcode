#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
        os << element;
    }
    os << endl;
    return os;
}

class Solution {
public:
    bool isValidSudoku(vector<vector<char>> &board) {
        bool row_appeared[9];
        bool column_appeared[9];
        bool block_appeared[9];
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                row_appeared[j] = false;
                column_appeared[j] = false;
                block_appeared[j] = false;
            }
            for (int j = 0; j < 9; ++j) {
                //row
                if (board[i][j] != '.') {
                    if (row_appeared[board[i][j] - '1'])
                        return false;
                    row_appeared[board[i][j] - '1'] = true;
                }
                //column
                if (board[j][i] != '.') {
                    if (column_appeared[board[j][i] - '1'])
                        return false;
                    column_appeared[board[j][i] - '1'] = true;
                }
                // block
                // i block index
                // j cell index
                int ri = (i / 3) * 3 + j / 3; //row index
                int ci = (i % 3) * 3 + j % 3; //column index
                if (board[ri][ci] != '.') {
                    if (block_appeared[board[ri][ci] - '1'])
                        return false;
                    block_appeared[board[ri][ci] - '1'] = true;
                }
            }
        }
        return true;
    }
};


TEST_CASE("Valid Sudoku - Example 1") {
    vector<vector<char>> input{
            {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };
    cout << input;
    REQUIRE(Solution().isValidSudoku(input));
}


TEST_CASE("Valid Sudoku - Example 2") {
    vector<vector<char>> input{
            {'8', '3', '.', '.', '7', '.', '.', '.', '.'},
            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };
    cout << input;
    REQUIRE(!Solution().isValidSudoku(input));
}
