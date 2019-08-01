#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int> &nums) {
        int result = INT_MIN;
        int min = 0;
        int accumulate = 0;
        for (int num : nums) {
            accumulate += num;
            if (accumulate - min > result)
                result = accumulate - min;
            if (accumulate < min)
                min = accumulate;
        }
        return result;
    }
};

TEST_CASE("Maximum Subarray") {
    vector<int> input{-2, 1, -3, 4, -1, 2, 1, -5, 4};
    REQUIRE(Solution().maxSubArray(input) == 6);
}

TEST_CASE("Maximum Subarray - Wrong Answer 1") {
    vector<int> input{-1};
    REQUIRE(Solution().maxSubArray(input) == -1);
}

TEST_CASE("Maximum Subarray - Wrong Answer 2") {
    vector<int> input{-2, -1};
    REQUIRE(Solution().maxSubArray(input) == -1);
}

TEST_CASE("Maximum Subarray - Wrong Answer 3") {
    vector<int> input{1, 2};
    REQUIRE(Solution().maxSubArray(input) == 3);
}
