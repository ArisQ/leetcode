#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    bool canJump(vector<int> &nums) {
        int nums_size = nums.size();
        if (nums_size <= 1)
            return true;
        int max_reach = nums[0];
        if (max_reach >= nums_size - 1)
            return true;
        for (int i = 1; i < nums_size; ++i) {
            if (i > max_reach) {
                return false;
            }
            if (i + nums[i] > max_reach) {
                max_reach = i + nums[i];
                if (max_reach >= nums_size - 1)
                    return true;
            }
        }
        return false;
    }
};

TEST_CASE("Jump Game - Example 1") {
    vector<int> input{2, 3, 1, 1, 4};
    REQUIRE(Solution().canJump(input));
}

TEST_CASE("Jump Game - Example 2") {
    vector<int> input{3, 2, 1, 0, 4};
    REQUIRE(!Solution().canJump(input));
}

