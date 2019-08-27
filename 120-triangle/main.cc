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
    int minimumTotal(vector<vector<int>> &triangle) {
        int triangleSize = triangle.size();
        if (triangleSize >= 2) {
            triangle[1][0] += triangle[0][0];
            triangle[1][1] += triangle[0][0];
        }
        for (int i = 2; i < triangleSize; ++i) {
            triangle[i][0] += triangle[i - 1][0];
            for (int j = 1; j < i ; ++j)
                triangle[i][j] += min(triangle[i - 1][j - 1], triangle[i - 1][j]);
            triangle[i][i] += triangle[i - 1][i - 1];
        }
        cout << triangle;
        int result = triangle[triangleSize - 1][0];
        for (int i = 1; i < triangleSize; ++i)
            result = min(result, triangle[triangleSize - 1][i]);
        return result;
    }
};

TEST_CASE("Triangle") {
    vector<vector<int>> input{
        {2},
        {3, 4},
        {6, 5, 7},
        {4, 1, 8, 3}
    };
    REQUIRE(Solution().minimumTotal(input) == 11);
}

TEST_CASE("Triangle - Wrong Answer 1") {
    vector<vector<int>> input{
        {-1},
        {3, 2},
        {-3, 1, -1}
    };
    REQUIRE(Solution().minimumTotal(input) == -1);
}
