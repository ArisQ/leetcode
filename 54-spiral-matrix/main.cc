#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix) {
        vector<int> result;
        if (matrix.empty())
            return result;
        int row_min = 0, row_max = matrix.size() - 1, column_min = 0, column_max = matrix[0].size() - 1;
        while (row_min < row_max && column_min < column_max) {
            for (int i = column_min; i < column_max; ++i)
                result.push_back(matrix[row_min][i]);
            for (int i = row_min; i < row_max; ++i)
                result.push_back(matrix[i][column_max]);
            for (int i = column_max; i > column_min; --i)
                result.push_back(matrix[row_max][i]);
            for (int i = row_max; i > row_min; --i)
                result.push_back(matrix[i][column_min]);
            ++row_min;
            --row_max;
            ++column_min;
            --column_max;
        }
        if (row_min == row_max && column_min <= column_max) {
            for (int i = column_min; i <= column_max; ++i)
                result.push_back(matrix[row_min][i]);
        } else if (column_min == column_max && row_min < row_max) {
            for (int i = row_min; i <= row_max; ++i)
                result.push_back(matrix[i][column_min]);
        }
        return result;
    }
};

TEST_CASE("Spiral Matrix - Example 1") {
    vector<vector<int>> input{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    vector<int> output{1, 2, 3, 6, 9, 8, 7, 4, 5};
    REQUIRE(Solution().spiralOrder(input) == output);
}

TEST_CASE("Spiral Matrix - Example 2") {
    vector<vector<int>> input{
        {1, 2,  3,  4},
        {5, 6,  7,  8},
        {9, 10, 11, 12}
    };
    vector<int> output{1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7};
    REQUIRE(Solution().spiralOrder(input) == output);
}

TEST_CASE("Spiral Matrix - Empty") {
    vector<vector<int>> input{};
    vector<int> output{};
    REQUIRE(Solution().spiralOrder(input) == output);
}

TEST_CASE("Spiral Matrix - Single") {
    vector<vector<int>> input{{1}};
    vector<int> output{1};
    REQUIRE(Solution().spiralOrder(input) == output);
}

TEST_CASE("Spiral Matrix - 2X2") {
    vector<vector<int>> input{
        {1, 2},
        {3, 4}
    };
    vector<int> output{1, 2, 4, 3};
    REQUIRE(Solution().spiralOrder(input) == output);
}
