#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        if (matrix.empty() || matrix[0].empty())
            return false;
        int m = matrix.size();
        int n = matrix[0].size();
        cout << m << " " << n << endl;
        if (matrix[0][0] == target || matrix[m - 1][n - 1] == target)
            return true;
        if (matrix[0][0] > target)
            return false;
        if (matrix[m - 1][n - 1] < target)
            return false;
        int sx = 0, sy = 0, s = 0;
        int ex = m - 1, ey = n - 1, e = m * n - 1;
        int px, py, p;
        cout << m << " " << n << endl;
        while (s + 1 < e) {
            cout << s << " " << e << endl;
            p = (e + s) / 2;
            px = p / n;
            py = p % n;
            cout << p << " " << px << " " << py << endl;
            if (matrix[px][py] == target)
                return true;
            else if (matrix[px][py] < target) {
                sx = px;
                sy = py;
                s = p;
            } else {
                ex = px;
                ey = py;
                e = p;
            }
        }
        return false;
    }
};
//
//TEST_CASE("Search a 2D Matrix - Example 1") {
//    vector<vector<int>> matrix = {
//        {1,  3,  5,  7},
//        {10, 11, 16, 20},
//        {23, 30, 34, 50}
//    };
//    REQUIRE(Solution().searchMatrix(matrix, 3) == true);
//}
//
//TEST_CASE("Search a 2D Matrix - Example 2") {
//    vector<vector<int>> matrix = {
//        {1,  3,  5,  7},
//        {10, 11, 16, 20},
//        {23, 30, 34, 50}
//    };
//    REQUIRE(Solution().searchMatrix(matrix, 13) == false);
//}
//
//TEST_CASE("Search a 2D Matrix - Wrong Answer 1") {
//    vector<vector<int>> matrix = {{}};
//    REQUIRE(Solution().searchMatrix(matrix, 1) == false);
//}

TEST_CASE("Search a 2D Matrix - Wrong Answer 2") {
    vector<vector<int>> matrix = {{1, 3, 5}};
    REQUIRE(Solution().searchMatrix(matrix, 2) == false);
}
