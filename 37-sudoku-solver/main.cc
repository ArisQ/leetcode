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
    cout << endl;
}

void printPossible(const bool (&possible)[9][9][9]) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            for (int k = 0; k < 9; ++k) {
                cout << possible[i][k][j];
            }
            cout << " ";
        }
        cout << endl;
    }
}


struct BoardPosition {
    int i;
    int j;
};
struct PossibleModified {
    int i;
    int j;
    int v;
};

ostream &operator<<(ostream &os, BoardPosition &p) {
    os << "<" << p.i << "," << p.j << "> ";
    return os;
}

ostream &operator<<(ostream &os, PossibleModified &p) {
    os << "<" << p.i << "," << p.j << "|" << p.v << "> ";
    return os;
}

class Solution {
public:
    void findNextNotDetermined(int (&possible_count)[9][9], int &i, int &j) {
        //从i，j往后，找到下一个未确定的位置，修改i，j后返回
        for (; j < 9; ++j)
            if (possible_count[i][j] > 1)
                return;

        for (; i < 9; ++i) {
            for (j = 0; j < 9; ++j)
                if (possible_count[i][j] > 1)
                    return;
        }
    }


    bool disableValueAtPosition(vector<vector<char>> &board,
                                bool (&possible)[9][9][9],
                                int (&possible_count)[9][9],
                                int i, int j, int value,
                                vector<PossibleModified> *possible_modified = nullptr,
                                vector<BoardPosition> *board_determined = nullptr
    ) {
        //设置i，j位置上不可能填入value；修改过的possible和board位置保存到vector中返回
        //有冲突返回false，否则返回true
//        if (!possible[i][j][value])
//            return true; // already false; do nothing; should occur
        if (possible_count[i][j] == 1)
            return false;
        possible[i][j][value] = false;
        --possible_count[i][j];
        if (possible_modified)
            possible_modified->push_back({i, j, value});
//        if (possible_count[i][j] == 0) {
//            return false;
//        }
        if (possible_count[i][j] == 1) { // && board[i][k]=='.'
            for (int l = 0; l < 9; ++l)
                if (possible[i][j][l]) {
                    board[i][j] = '1' + char(l);
                    if (board_determined)
                        board_determined->push_back({i, j});
                    return determine(board, possible, possible_count, i, j, possible_modified, board_determined);
                }
        }
        return true;
    }

    bool determine(vector<vector<char>> &board,
                   bool (&possible)[9][9][9],
                   int (&possible_count)[9][9],
                   int i, int j,
                   vector<PossibleModified> *possible_modified = nullptr,
                   vector<BoardPosition> *board_determined = nullptr
    ) {
        //确定i，j位置上的值，在同行，同列，同块的位置上禁用确定的值，成功返回true，冲突返回false
        int value = board[i][j] - '1';
        possible_count[i][j] = 1;
        for (int k = 0; k < 9; ++k)
            if (k != value && possible[i][j][k]) {
                possible[i][j][k] = false;
                if (possible_modified)
                    possible_modified->push_back({i, j, k});
            }

        int block_start_r = (i / 3) * 3;
        int block_start_c = (j / 3) * 3;
        for (int k = 0; k < 9; ++k) {
            if (possible[i][k][value] && k != j) {
                if (!disableValueAtPosition(board, possible, possible_count, i, k, value, possible_modified,
                                            board_determined))
                    return false;
            }
            if (possible[k][j][value] && k != i) {
                if (!disableValueAtPosition(board, possible, possible_count, k, j, value, possible_modified,
                                            board_determined))
                    return false;
            }
            int r = block_start_r + k / 3;
            int c = block_start_c + k % 3;
            if (possible[r][c][value] && !(r == i && c == j)) {
                if (!disableValueAtPosition(board, possible, possible_count, r, c, value, possible_modified,
                                            board_determined))
                    return false;
            }
        }
        return true;
    }

    void restoreBoardAndPossible(vector<vector<char>> &board,
                                 bool (&possible)[9][9][9],
                                 int (&possible_count)[9][9],
                                 vector<PossibleModified> &possible_modified,
                                 vector<BoardPosition> &board_determined
    ) {
        for (auto m:board_determined)
            board[m.i][m.j] = '.';
        for (auto m:possible_modified) {
            possible[m.i][m.j][m.v] = true;
            ++possible_count[m.i][m.j];
        }
        board_determined.clear();
        possible_modified.clear();
    }

    bool trySolveSudoku(vector<vector<char>> &board,
                        bool (&possible)[9][9][9],
                        int (&possible_count)[9][9],
                        const int i, const int j //try position
    ) {
        //尝试i，j位置上的每一种可能，并递归尝试后续位置；成功返回true，存在冲突返回alse
        vector<PossibleModified> possible_modified;
        vector<BoardPosition> board_determined;
        for (int v = 0; v < 9; ++v) {
            if (!possible[i][j][v])
                continue;
            board[i][j] = v + '1';
            board_determined.push_back({i, j});
            if (!determine(board, possible, possible_count, i, j, &possible_modified, &board_determined)) {
                //设置为v后有冲突，恢复possible
                restoreBoardAndPossible(board, possible, possible_count, possible_modified, board_determined);
                continue;
            }
            //没有冲突，继续尝试后续位置
            int next_i = i, next_j = j;
            findNextNotDetermined(possible_count, next_i, next_j);
            if (next_i == 9)
                return true;
            if (trySolveSudoku(board, possible, possible_count, next_i, next_j))
                return true;//只找答案，假设解法唯一，因此直接返回
            //设置为v后，后续无解，恢复possible
            restoreBoardAndPossible(board, possible, possible_count, possible_modified, board_determined);
        }
        return false;
    }

    void solveSudoku(vector<vector<char>> &board) {
        bool possible[9][9][9]; //[i][j][k] 第i行第j列，是否可能是k（字符为'1'+k）
        int possible_count[9][9]; //[i][j]位置，还有多少种可能，即\sigma_{k}{possible[i][j][k]}；用于快速判断，避免遍历possible
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j) {
                for (int k = 0; k < 9; ++k) {
                    possible[i][j][k] = true;
                }
                possible_count[i][j] = 9;
            }

        // 根据已经确定的数字，去除同行，同列，同块的其他位置的可能性
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] != '.' && possible_count[i][j] != 1) //==1 means already determined
                    determine(board, possible, possible_count, i, j);
            }
        }
        //无法通过已有数字推导得到，依次尝试，看是否有冲突
        int i = 0, j = 0;
        findNextNotDetermined(possible_count, i, j);//找到第一个有多种可能的，未确定的位置
        if (i < 9)
            trySolveSudoku(board, possible, possible_count, i, j);// false : no answer
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
    Solution().solveSudoku(input);
    cout << input;
    REQUIRE(input == output);
}


TEST_CASE("Sudoku Solver - Wrong Answer 1") {
    vector<vector<char>> input{
        {'.', '.', '9', '7', '4', '8', '.', '.', '.'},
        {'7', '.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '2', '.', '1', '.', '9', '.', '.', '.'},
        {'.', '.', '7', '.', '.', '.', '2', '4', '.'},
        {'.', '6', '4', '.', '1', '.', '5', '9', '.'},
        {'.', '9', '8', '.', '.', '.', '3', '.', '.'},
        {'.', '.', '.', '8', '.', '3', '.', '2', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.', '6'},
        {'.', '.', '.', '2', '7', '5', '9', '.', '.'}
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
    Solution().solveSudoku(input);
    cout << input;
    REQUIRE(input == output);
}

TEST_CASE("Sudoku Solver - Wrong Answer 2") {
    vector<vector<char>> input{
        {'.', '.', '.', '2', '.', '.', '.', '6', '3'},
        {'3', '.', '.', '.', '.', '5', '4', '.', '1'},
        {'.', '.', '1', '.', '.', '3', '9', '8', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '9', '.'},
        {'.', '.', '.', '5', '3', '8', '.', '.', '.'},
        {'.', '3', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '2', '6', '3', '.', '.', '5', '.', '.'},
        {'5', '.', '3', '7', '.', '.', '.', '.', '8'},
        {'4', '7', '.', '.', '.', '1', '.', '.', '.'}
    };
    vector<vector<char>> output{
        {'8', '5', '4', '2', '1', '9', '7', '6', '3'},
        {'3', '9', '7', '8', '6', '5', '4', '2', '1'},
        {'2', '6', '1', '4', '7', '3', '9', '8', '5'},
        {'7', '8', '5', '1', '2', '6', '3', '9', '4'},
        {'6', '4', '9', '5', '3', '8', '1', '7', '2'},
        {'1', '3', '2', '9', '4', '7', '8', '5', '6'},
        {'9', '2', '6', '3', '8', '4', '5', '1', '7'},
        {'5', '1', '3', '7', '9', '2', '6', '4', '8'},
        {'4', '7', '8', '6', '5', '1', '2', '3', '9'}
    };
    cout << input;

    Solution().solveSudoku(input);
    cout << input;
    REQUIRE(input == output);
}
