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
    vector<vector<int>> permute(vector<int> &nums) {
        vector<vector<int>> result;
        permute(nums, 0, nums.size(), result);
        return result;
    }

    void permute(vector<int> &nums, int i, int n, vector<vector<int>> &result) {
        if (i >= n)
            return;
        if (i == n - 1)
            result.push_back(nums);
        for (int j = i; j < n; ++j) {
            swap(nums[i], nums[j]);
            permute(nums, i + 1, n, result);
        }
        int num_end = nums[i];
        for (int j = i; j + 1 < n; ++j) {
            nums[j] = nums[j + 1];
        }
        nums[n - 1] = num_end;
    }
};

TEST_CASE("Permutations") {

    vector<int> input{1, 2, 3};
    vector<vector<int>> output{
        {1, 2, 3},
        {1, 3, 2},
        {2, 1, 3},
        {2, 3, 1},
        {3, 1, 2},
        {3, 2, 1}
    };
    cout << input << endl << output << endl;
    REQUIRE(Solution().permute(input) == output);
}

