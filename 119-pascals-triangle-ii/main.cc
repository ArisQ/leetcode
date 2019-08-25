#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
//        os.width(3);
        os << element<<" ";
    }
    os << endl;
    return os;
}

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        if (rowIndex == 0)
            return vector<int>{1};
        vector<int> result(rowIndex + 1, 1);
        for (int i = 2; i <= rowIndex; ++i) {
//            result[i] = 1;
            for (int j = i - 1; j > 0; --j) {
                result[j] += result[j - 1];
            }
            cout << result;
        }
        return result;
    }
};

TEST_CASE("Pascal's Triangle II") {
    vector<int> output = {1, 3, 3, 1};
    REQUIRE(Solution().getRow(3) == output);
    Solution().getRow(33);
}

TEST_CASE("Pascal's Triangle - 0") {
    vector<int> output{1};
    REQUIRE(Solution().getRow(0) == output);
}

TEST_CASE("Pascal's Triangle - 1") {
    vector<int> output = {1, 1};
    REQUIRE(Solution().getRow(1) == output);
}

TEST_CASE("Pascal's Triangle - 2") {
    vector<int> output = {1, 2, 1};
    REQUIRE(Solution().getRow(2) == output);
}
