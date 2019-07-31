#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
        cout.width(3);
        os << element;
    }
    os << endl;
    return os;
}

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int> &nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        permute(nums, 0, result);
        return result;
    }

    void permute(vector<int> &nums, int i, vector<vector<int>> &result) {
        int n = nums.size();
        if (i >= n)
            return;
        if (i == n - 1)
            result.push_back(nums);
        permute(nums, i + 1, result);
        for (int j = i + 1; j < n; ++j) {
            while (j < n && nums[i] == nums[j])
                ++j;
            if (j == n)
                break;
            swap(nums[i], nums[j]);
            permute(nums, i + 1, result);
        }
        int num_end = nums[i];
        for (int j = i; j + 1 < n; ++j) {
            nums[j] = nums[j + 1];
        }
        nums[n - 1] = num_end;
    }
};

TEST_CASE("Permutations II") {

    vector<int> input{1, 1, 2};
    vector<vector<int>> output{
        {1, 1, 2},
        {1, 2, 1},
        {2, 1, 1}
    };
    cout << input << endl << output << endl;
    REQUIRE(Solution().permuteUnique(input) == output);
}
