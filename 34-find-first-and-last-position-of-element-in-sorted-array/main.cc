#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int> &nums, int target) {
        vector<int> result{-1, -1};
        if (nums.empty())
            return result;
        int i = 0; //nums[i]<=target
        int j = nums.size() - 1; //nums[j]>=target
        int m; //m=(i+j)/2  nums[m]!=target
        if (nums[i] > target || nums[j] < target)
            return result;
        //二分法找到包含所有target的区间
        while (i < j) {
            m = (i + j) / 2;
            if (nums[m] < target)
                i = m + 1;
            else if (nums[m] > target)
                j = m;
            else
                break; //nums[m]==target
        }
        if (i == j) {
            if (nums[i] == target) {
                result[0] = i;
                result[1] = i;
            }
            return result;
        }
        //nums[i]<=target<=nums[j] && [0..i-1]<target, [j+1,...]>target
        //分别找target的最左和最右点
        int mi = i, mj = j;
        while (mi < mj) {
            m = (mi + mj) / 2;
            if (nums[m] < target)
                mi = m + 1;
            else
                mj = m;
        }
        result[0] = mi;
        mi = i;
        mj = j;
        while (mi < mj) {
            m = (mi + mj + 1) / 2;
            if (nums[m] <= target)
                mi = m;
            else
                mj = m - 1;
        }
        result[1] = mi;
        return result;
    }
};


TEST_CASE("Find First and Last Position of Element in Sorted Array - Example 1") {
    vector<int> nums = {5, 7, 7, 8, 8, 10};
    vector<int> output{3, 4};
    REQUIRE(Solution().searchRange(nums, 8) == output);
}

TEST_CASE("Find First and Last Position of Element in Sorted Array - Example 2") {
    vector<int> nums = {5, 7, 7, 8, 8, 10};
    vector<int> output{-1, -1};
    REQUIRE(Solution().searchRange(nums, 6) == output);
}

TEST_CASE("Find First and Last Position of Element in Sorted Array - Empty") {
    vector<int> nums = {};
    vector<int> output{-1, -1};
    REQUIRE(Solution().searchRange(nums, 6) == output);
}

TEST_CASE("Find First and Last Position of Element in Sorted Array - Single Not Found") {
    vector<int> nums = {1};
    vector<int> output{-1, -1};
    REQUIRE(Solution().searchRange(nums, 6) == output);
}

TEST_CASE("Find First and Last Position of Element in Sorted Array - Single Match") {
    vector<int> nums = {1};
    vector<int> output{0, 0};
    REQUIRE(Solution().searchRange(nums, 1) == output);
}
