#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    int search(vector<int> &nums, int target) {
        if (nums.empty())
            return -1;
        int i = 0;
        int j = nums.size() - 1;
        while (i + 1 < j) {
            int m = (j + i) / 2;
            if (nums[i] < nums[j]) {
                // i j  ascending
                if (nums[m] < target)
                    i = m;
                else
                    j = m;
            } else {
                //  i j rotated
                if (nums[i] < nums[m]) {
                    //i...m ascending  m...j rotated
                    if (nums[i] <= target && nums[m] >= target) {
                        j = m;
                    } else {
                        i = m;
                    }
                } else {
                    //i...m rotated    m...j  ascending
                    if (nums[m] <= target && nums[j] >= target) {
                        i = m;
                    } else {
                        j = m;
                    }
                }
            }
        }
        //i<=j  i+1>=j
        if (nums[i] == target)
            return i;
        else if (nums[j] == target)
            return j;
        else
            return -1;
    }
};

TEST_CASE("Search in Rotated Sorted Array - Example 1") {
    vector<int> input{4, 5, 6, 7, 0, 1, 2};
    REQUIRE(Solution().search(input, 0) == 4);
}

TEST_CASE("Search in Rotated Sorted Array - Example 2") {
    vector<int> input{4, 5, 6, 7, 0, 1, 2};
    REQUIRE(Solution().search(input, 3) == -1);
}

TEST_CASE("Search in Rotated Sorted Array - Empty") {
    vector<int> input;
    REQUIRE(Solution().search(input, 5) == -1);
}
