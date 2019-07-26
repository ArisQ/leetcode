#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
        os << element << " ";
    }
    os << endl;
    return os;
}

class Solution {
public:
    int firstMissingPositive(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        auto iter = nums.begin();
        while (iter != nums.end() && *iter <= 0)
            ++iter;
        int result = 1;
        while (iter != nums.end()) {
            if (*iter != result)
                return result;
            while (iter != nums.end() && *(iter) == (result)) {
                ++iter;
            }
            ++result;
        }
        return result;
    }
};

TEST_CASE("First Missing Positive - Example 1") {
    vector<int> input{1, 2, 0};
    REQUIRE(Solution().firstMissingPositive(input) == 3);
}

TEST_CASE("First Missing Positive - Example 2") {
    vector<int> input{3, 4, -1, 1};
    REQUIRE(Solution().firstMissingPositive(input) == 2);
}

TEST_CASE("First Missing Positive - Example 3") {
    vector<int> input{7, 8, 9, 11, 12};
    REQUIRE(Solution().firstMissingPositive(input) == 1);
}

TEST_CASE("First Missing Positive - Wrong Answer 1") {
    vector<int> input{0, 2, 2, 1, 1};
    REQUIRE(Solution().firstMissingPositive(input) == 3);
}
