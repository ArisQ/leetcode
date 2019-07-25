#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int> &nums, int target) {
        if (nums.empty())
            return 0;
        int i = 0;
        int j = nums.size() - 1;
        if (nums[i] >= target)
            return i;
        if (nums[j] == target)
            return j;
        if (nums[j] < target)
            return j + 1;
        //
        int m;
        while (i + 1 < j) {
            // loop invariant: nums[i] < target < nums[j]
            m = (i + j) / 2;
            if (nums[m] == target)
                return m;
            else if (nums[m] < target)
                i = m;
            else // nums[m]>target
                j = m;
        }
        //not found && j=i+1
        return j;
    }
};


TEST_CASE("Search Insert Position") {
    vector<int> input{1, 3, 5, 6};
    REQUIRE(Solution().searchInsert(input, 5) == 2);
}

TEST_CASE("Search Insert Position") {
    vector<int> input{1, 3, 5, 6};
    REQUIRE(Solution().searchInsert(input, 2) == 1);
}

TEST_CASE("Search Insert Position") {
    vector<int> input{1, 3, 5, 6};
    REQUIRE(Solution().searchInsert(input, 7) == 4);
}

TEST_CASE("Search Insert Position") {
    vector<int> input{1, 3, 5, 6};
    REQUIRE(Solution().searchInsert(input, 0) == 0);
}

