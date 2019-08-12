#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <set>

using namespace std;

class Solution {
    int n;
    vector<vector<int>> result;
    vector<int> selected;
public:
    vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        n = nums.size();
        selected.reserve(n);
        result.reserve(1 << n);
        select(nums, 0);
        return result;
    }

    void select(vector<int> &nums, int index) {
        if (index == n) {
            result.push_back(selected);
            return;
        }
        int dupCount = 1;
        while (index + dupCount < n && nums[index] == nums[index + dupCount])
            ++dupCount;
        select(nums, index + dupCount);
        for (int i = 0; i < dupCount; ++i) {
            selected.push_back(nums[index + i]);
            select(nums, index + dupCount);
        }
        for (int i = 0; i < dupCount; ++i)
            selected.pop_back();
    }
};

TEST_CASE("Subsets II") {
    vector<int> nums{1, 2, 3};
    vector<vector<int>> output{
        {3},
        {1},
        {2},
        {1, 2, 3},
        {1, 3},
        {2, 3},
        {1, 2},
        {}
    };
    auto answer = Solution().subsetsWithDup(nums);
    REQUIRE(multiset<vector<int>>(answer.begin(), answer.end()) == multiset<vector<int>>(output.begin(), output.end()));
}
