#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <unordered_set>

using namespace std;

class Solution1 {
public:
    int singleNumber(const vector<int> &nums) {
        // HashSet
        unordered_set<int> set;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (set.find(nums[i]) == set.end()) {
                set.insert(nums[i]);
            } else {
                set.erase(nums[i]);
            }
        }
        return *set.cbegin();
    }
};

class Solution2 {
public:
    int singleNumber(vector<int> &nums) {
        return findSingle(nums, 0, nums.size());
    }
    int findSingle(vector<int> &nums, int s, int e) {
        if (s + 1 == e)
            return nums[s];
        int r = rand() % (e - s) + s;
        swap(nums[e - 1], nums[r]);
        int next = s;
        for (int i = s; i < e - 1; ++i) {
            if (nums[i] < nums[e - 1]) {
                swap(nums[next], nums[i]);
                ++next;
            } else if (nums[i] == nums[e - 1]) {
                // s<=next<=i 注意不要覆盖
                int temp = nums[i];
                nums[i] = nums[next];
                nums[next] = nums[s];
                nums[s] = temp;
                ++next;
            }
        }

        if (nums[s] != nums[e - 1])
            return nums[e - 1];
        if ((next - s - 1) % 2 == 1)
            return findSingle(nums, s + 1, next);
        else  // (e-1-next)%2==1
            return findSingle(nums, next, e - 1);
    }
};

TEST_CASE("Single Number") {
    REQUIRE(Solution1().singleNumber({2, 2, 1}) == 1);
    REQUIRE(Solution1().singleNumber({4, 1, 2, 1, 2}) == 4);

    vector<int> nums1{2, 2, 1};
    REQUIRE(Solution2().singleNumber(nums1) == 1);
    vector<int> nums2{4, 1, 2, 1, 2};
    REQUIRE(Solution2().singleNumber(nums2) == 4);
}
