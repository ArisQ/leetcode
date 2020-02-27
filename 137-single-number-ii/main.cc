#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int> &nums) {
        return findSingle(nums, 0, nums.size());
    }
    int findSingle(vector<int> &nums, int s, int e) {
        if (s + 1 == e)
            return nums[s];
        int r = rand() % (e - s) + s;
        int next = s;
        int same_next = s;
        swap(nums[r], nums[e - 1]);
        for (int i = s; i < e - 1; ++i) {
            if (nums[i] < nums[e - 1]) {
                swap(nums[i], nums[next]);
                ++next;
            } else if (nums[i] == nums[e - 1]) {
                int temp = nums[i];
                nums[i] = nums[next];
                nums[next] = nums[same_next];
                nums[same_next] = temp;
                ++next;
                ++same_next;
            }
        }
        if (nums[s] != nums[e - 1])
            return nums[e - 1];
        if ((next - s - 2) % 3 == 0)
            return findSingle(nums, next, e - 1);
        else
            return findSingle(nums, s + 2, next);
    }
};

TEST_CASE("Single Number II") {
    vector<int> nums1{2, 2, 3, 2};
    REQUIRE(Solution().singleNumber(nums1) == 3);
    vector<int> nums2{0, 1, 0, 1, 0, 1, 99};
    REQUIRE(Solution().singleNumber(nums2) == 99);
}
