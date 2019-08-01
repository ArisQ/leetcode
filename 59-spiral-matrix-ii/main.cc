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
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> result(n, vector<int>(n, 0));
        int i = 0, j = 0;
        int di = 0, dj = 1;
        int n_2 = n * n;
        int next_i, next_j;
        for (int k = 1; k <= n_2; ++k) {
            result[i][j] = k;
            next_i = i + di;
            next_j = j + dj;
            if (next_i < 0 || next_i >= n || next_j < 0 || next_j >= n || result[next_i][next_j] != 0) {
                // 换向，顺序为 0,1 => 1,0 => 0,-1 => -1,0 => 0,1
                if (dj == 0) {
                    dj = -di;
                    di = 0;
                } else {
                    di = dj;
                    dj = 0;
                }
            }
            i += di;
            j += dj;
        }
        return result;
    }
};

TEST_CASE("Spiral Matrix II") {
    vector<vector<int>> spiral_matrix_3{
        {1, 2, 3},
        {8, 9, 4},
        {7, 6, 5}
    };
    REQUIRE(Solution().generateMatrix(3) == spiral_matrix_3);
    for (int i = 1; i < 10; ++i)
        cout << Solution().generateMatrix(i) << endl;
}
