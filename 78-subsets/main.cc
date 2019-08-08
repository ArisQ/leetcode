#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
        os.width(3);
        os << element;
    }
    os << endl;
    return os;
}

class Solution {
public:
    vector<vector<int>> subsets(vector<int> &nums) {
        int n = nums.size();
        vector<vector<int>> result;
        vector<int> selected;
        selected.reserve(n);
        result.reserve(1 << n);
        select(result, selected, nums, 0);
        cout << result;
        return result;
    }

    void select(vector<vector<int>> &result, vector<int> &selected, vector<int> &nums, int index) {
        if (index == nums.size()) {
            result.push_back(selected);
            return;
        }
        select(result, selected, nums, index + 1);
        selected.push_back(nums[index]);
        select(result, selected, nums, index + 1);
        selected.pop_back();
    }
};

TEST_CASE("Subsets") {
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> output = {
        {3},
        {1},
        {2},
        {1, 2, 3},
        {1, 3},
        {2, 3},
        {1, 2},
        {}
    };
    auto answer = Solution().subsets(nums);
    REQUIRE(multiset<vector<int>>(answer.begin(), answer.end()) == multiset<vector<int>>(output.begin(), output.end()));
}
