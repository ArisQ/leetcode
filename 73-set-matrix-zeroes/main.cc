#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
        os.width(3);
        os << element;
    }
    os << endl;
    return os;
}

class Solution {
public:
    void setZeroes(vector<vector<int>> &matrix) {
        if (matrix.empty())
            return;;
        set<int> row, column;
        int m = matrix.size();
        int n = matrix[0].size();
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (matrix[i][j] == 0) {
                    row.insert(i);
                    column.insert(j);
                }
        for (auto c:column) {
            cout << c << " ";
        }
        cout << endl;
        for (auto c:column) {
            for (int i = 0; i < m; ++i)
                matrix[i][c] = 0;
        }
        for (auto r:row) {
            for (int i = 0; i < n; ++i)
                matrix[r][i] = 0;
        }
        for (auto c:column) {
            for (int i = 0; i < m; ++i)
                matrix[i][c] = 0;
        }
    }
};

TEST_CASE("Set Matrix Zeroes - Example 1") {
    vector<vector<int>> input{
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    };
    vector<vector<int>> output{
        {1, 0, 1},
        {0, 0, 0},
        {1, 0, 1}
    };
    cout << input;
    cout << output;
    Solution().setZeroes(input);
    cout << input;
    REQUIRE(input == output);
}

TEST_CASE("Set Matrix Zeroes - Example 2") {
    vector<vector<int>> input{
        {0, 1, 2, 0},
        {3, 4, 5, 2},
        {1, 3, 1, 5}
    };
    vector<vector<int>> output{
        {0, 0, 0, 0},
        {0, 4, 5, 0},
        {0, 3, 1, 0}
    };
    cout << input;
    cout << output;
    Solution().setZeroes(input);
    cout << input;
    REQUIRE(input == output);
}

