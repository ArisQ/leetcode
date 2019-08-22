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
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> result;
        if (numRows <= 0)
            return result;
        result.emplace_back(vector<int>{1});
        if (numRows == 1)
            return result;
        result.emplace_back(vector<int>{1, 1});
        for (int i = 2; i < numRows; ++i) {
            cout << "i " << i << endl;
            vector<int> row(result[i - 1].size() + 1);
            row[0] = 1;
            row[result[i - 1].size()] = 1;
            for (int j = 0; j < i - 1; ++j) {
                cout << "j " << j << endl;
                row[j + 1] = result[i - 1][j] + result[i - 1][j + 1];
            }
            result.emplace_back(row);
        }
        cout << result;
        return result;
    }
};

TEST_CASE("Pascal's Triangle") {
    vector<vector<int>> output{
        {1},
        {1, 1},
        {1, 2, 1},
        {1, 3, 3, 1},
        {1, 4, 6, 4, 1}
    };
    REQUIRE(Solution().generate(5) == output);
}

TEST_CASE("Pascal's Triangle - 0") {
    vector<vector<int>> output{};
    REQUIRE(Solution().generate(0) == output);
}

TEST_CASE("Pascal's Triangle - 1") {
    vector<vector<int>> output{{1}};
    REQUIRE(Solution().generate(1) == output);
}

TEST_CASE("Pascal's Triangle - 2") {
    vector<vector<int>> output{
        {1},
        {1, 1}
    };
    REQUIRE(Solution().generate(2) == output);
}
