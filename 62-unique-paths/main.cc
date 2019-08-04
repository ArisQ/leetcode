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
    int uniquePaths(int m, int n) {
        vector<vector<int>> result(m, vector<int>(n, 1));
        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j)
                result[i][j] = result[i - 1][j] + result[i][j - 1];
        cout << result;
        return result[m - 1][n - 1];
    }
};

TEST_CASE("Unique Paths") {
    REQUIRE(Solution().uniquePaths(3, 2) == 3);
    REQUIRE(Solution().uniquePaths(7, 3) == 28);
}
