#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
        int i1 = m - 1, i2 = n - 1, ia = m + n - 1;
        for (; ia >= 0 && i1 >= 0 && i2 >= 0; --ia) {
            if (nums1[i1] < nums2[i2])
                nums1[ia] = nums2[i2--];
            else
                nums1[ia] = nums1[i1--];
        }
        if (i1 < 0) {
            for (; i2 >= 0; --ia, --i2)
                nums1[ia] = nums2[i2];
        }
        //i2<0  do nothing
    }
};

TEST_CASE("Merge Sorted Array") {
    vector<int> nums1{1, 2, 3, 0, 0, 0};
    vector<int> nums2{2, 5, 6};
    vector<int> output{1, 2, 2, 3, 5, 6};
    Solution().merge(nums1, 3, nums2, 3);
    REQUIRE(nums1 == output);
}
