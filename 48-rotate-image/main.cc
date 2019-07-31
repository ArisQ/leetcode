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

class Solution {
public:
    void rotate(vector<vector<int>> &matrix) {
        int n = matrix.size();
        if (n <= 1)
            return;
        for (int i = 0; i < n / 2; ++i)
            for (int j = 0; j < (n + 1) / 2; ++j) {
                cout << n << " " << i << " " << j << " " << n - 1 - i << " " << n - 1 - j << endl;
                int temp = matrix[i][j];
                matrix[i][j] = matrix[n - 1 - j][i];
                matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];
                matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];
                matrix[j][n - 1 - i] = temp;
            }
    }
};

TEST_CASE("Rotate Image - Example 1") {
    vector<vector<int>> input{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    vector<vector<int>> output{
        {7, 4, 1},
        {8, 5, 2},
        {9, 6, 3}
    };
    cout << input << output;
    Solution().rotate(input);
    cout << input;
    REQUIRE(input == output);
}

TEST_CASE("Rotate Image - Example 2") {
    vector<vector<int>> input{
        {5,  1,  9,  11},
        {2,  4,  8,  10},
        {13, 3,  6,  7},
        {15, 14, 12, 16}
    };
    vector<vector<int>> output{
        {15, 13, 2,  5},
        {14, 3,  4,  1},
        {12, 6,  8,  9},
        {16, 7,  10, 11}
    };
    Solution().rotate(input);
    REQUIRE(input == output);
}

