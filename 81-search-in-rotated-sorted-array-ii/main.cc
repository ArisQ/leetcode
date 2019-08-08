#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    bool search(vector<int> &nums, int target) {
        if (nums.empty())
            return false;
        int i = 0;
        int j = nums.size() - 1;
        while (i + 1 < j) {
            int m = (j + i) / 2;
            if (nums[i] < nums[j]) {
                //升序
                if (nums[m] < target)
                    i = m;
                else
                    j = m;
            } else {
                // nums[i]>=nums[j]  rotated or equal
                if (nums[i] < nums[m]) {
                    //i...m ascending  m...j rotated
                    if (nums[i] <= target && nums[m] >= target) {
                        j = m;
                    } else {
                        i = m;
                    }
                } else if (nums[j] > nums[m]) {
                    //i...m ascending  m...j rotated
                    if (nums[m] <= target && nums[j] >= target) {
                        i = m;
                    } else {
                        j = m;
                    }
                } else {
                    //nums[j]<=nums[m]<=nums[i]  ==> nums[j]=nums[m]=nums[i] 无法确定
                    for (m = i; m <= j; ++m)
                        if (nums[m] == target)
                            return true;
                    return false;
                }
            }
        }
        //i<=j  i+1>=j
        if (nums[i] == target || nums[j] == target)
            return true;
        return false;
    }
};

TEST_CASE("Search in Rotated Sorted Array II - Example 1") {
    vector<int> nums{2, 5, 6, 0, 0, 1, 2};
    REQUIRE(Solution().search(nums, 0) == true);
}

TEST_CASE("Search in Rotated Sorted Array II - Example 2") {
    vector<int> nums{2, 5, 6, 0, 0, 1, 2};
    REQUIRE(Solution().search(nums, 3) == false);
}

TEST_CASE("Search in Rotated Sorted Array II - Wrong Answer 1") {
    vector<int> nums{1, 1, 3, 1};
    REQUIRE(Solution().search(nums, 3) == true);
}
