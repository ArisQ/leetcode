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

void printPossibleCount(const int (&possible_count)[9][9]) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cout << possible_count[i][j];
        }
        cout << endl;
    }
}

void printPossible(const bool (&possible)[9][9][9]) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            for (int k = 0; k < 9; ++k) {
                cout << possible[j][k][i];
            }
            cout << " ";
        }
        cout << endl;
    }
}

int determine_count = 0;

class Solution {
public:
    void disable_value_at_position(vector<vector<char>> &board,
                                   bool (&possible)[9][9][9],
                                   int (&possible_count)[9][9],
                                   int i, int j, int value) {
        possible[i][j][value] = false;
        --possible_count[i][j];
        if (possible_count[i][j] == 1) { // && board[i][k]=='.'
            for (int l = 0; l < 9; ++l)
                if (possible[i][j][l]) {
                    board[i][j] = '1' + char(l);
                    determine(board, possible, possible_count, i, j);
                    break;
                }
        }
    }

    void determine(vector<vector<char>> &board,
                   bool (&possible)[9][9][9],
                   int (&possible_count)[9][9],
                   int i, int j) {
        int value = board[i][j] - '1';
        possible_count[i][j] = 1;
        for (int k = 0; k < 9; ++k)//no need
            if (k != value)
                possible[i][j][k] = false;

        int block_start_r = (i / 3) * 3;
        int block_start_c = (j / 3) * 3;
        for (int k = 0; k < 9; ++k) {
            if (possible[i][k][value] && k != j) {
                disable_value_at_position(board, possible, possible_count, i, k, value);
            }
            if (possible[k][j][value] && k != i) {
                disable_value_at_position(board, possible, possible_count, k, j, value);
            }
            int r = block_start_r + k / 3;
            int c = block_start_c + k % 3;
            if (possible[r][c][value] && !(r == i && c == j)) {
                disable_value_at_position(board, possible, possible_count, r, c, value);
            }
        }
    }

    void solveSudoku(vector<vector<char>> &board) {
        bool possible[9][9][9];
        int possible_count[9][9];
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j) {
                for (int k = 0; k < 9; ++k) {
                    possible[i][j][k] = true;
                }
                possible_count[i][j] = 9;
            }
        printPossibleCount(possible_count);
        printPossible(possible);

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] != '.' && possible_count[i][j] != 1) //==1 means already determined
                    determine(board, possible, possible_count, i, j);
            }
        }

        printPossibleCount(possible_count);
        printPossible(possible);
    }
};


TEST_CASE("Sudoku Solver") {
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
    vector<vector<char>> output{
            {'5', '3', '4', '6', '7', '8', '9', '1', '2'},
            {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
            {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
            {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
            {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
            {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
            {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
            {'2', '8', '7', '4', '1', '9', '6', '3', '5'},
            {'3', '4', '5', '2', '8', '6', '1', '7', '9'}
    };
    cout << input;
//    REQUIRE(Solution().solveSudoku(input));
    Solution().solveSudoku(input);
    cout << input;
    REQUIRE(input == output);
}


TEST_CASE("Sudoku Solver - Wrong Answer 1") {
//    vector<vector<char>> input{
//            {'.', '.', '9', '7', '4', '8', '.', '.', '.'},
//            {'7', '.', '.', '.', '.', '.', '.', '.', '.'},
//            {'.', '2', '.', '1', '.', '9', '.', '.', '.'},
//            {'.', '.', '7', '.', '.', '.', '2', '4', '.'},
//            {'.', '6', '4', '.', '1', '.', '5', '9', '.'},
//            {'.', '9', '8', '.', '.', '.', '3', '.', '.'},
//            {'.', '.', '.', '8', '.', '3', '.', '2', '.'},
//            {'.', '.', '.', '.', '.', '.', '.', '.', '6'},
//            {'.', '.', '.', '2', '7', '5', '9', '.', '.'}
//    };

    vector<vector<char>> input{
            {'.', '5', '9', '7', '4', '8', '.', '.', '.'},
            {'7', '.', '.', '6', '5', '2', '.', '.', '.'},
            {'.', '2', '.', '1', '.', '9', '.', '.', '.'},
            {'5', '.', '7', '9', '8', '6', '2', '4', '1'},
            {'2', '6', '4', '3', '1', '7', '5', '9', '8'},
            {'1', '9', '8', '5', '2', '4', '3', '6', '7'},
            {'.', '.', '.', '8', '6', '3', '.', '2', '.'},
            {'.', '.', '.', '4', '9', '1', '.', '.', '6'},
            {'.', '.', '.', '2', '7', '5', '9', '.', '.'},
    };

    vector<vector<char>> output{
            {'5', '1', '9', '7', '4', '8', '6', '3', '2'},
            {'7', '8', '3', '6', '5', '2', '4', '1', '9'},
            {'4', '2', '6', '1', '3', '9', '8', '7', '5'},
            {'3', '5', '7', '9', '8', '6', '2', '4', '1'},
            {'2', '6', '4', '3', '1', '7', '5', '9', '8'},
            {'1', '9', '8', '5', '2', '4', '3', '6', '7'},
            {'9', '7', '5', '8', '6', '3', '1', '2', '4'},
            {'8', '3', '2', '4', '9', '1', '7', '5', '6'},
            {'6', '4', '1', '2', '7', '5', '9', '8', '3'}
    };
    cout << input;
//    REQUIRE(Solution().solveSudoku(input));
    Solution().solveSudoku(input);
    cout << input;
    REQUIRE(input == output);
}
/*
[[".",".","9","7","4","8",".",".","."],
["7",".",".","6",".","2",".",".","."],
[".","2",".","1",".","9",".",".","."],
[".",".","7","9","8","6","2","4","1"],
["2","6","4","3","1","7","5","9","8"],
["1","9","8","5","2","4","3","6","7"],
[".",".",".","8","6","3",".","2","."],
[".",".",".","4","9","1",".",".","6"],
[".",".",".","2","7","5","9",".","."]]
 */
