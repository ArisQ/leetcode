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
    int removeDuplicates(vector<int> &nums) {
        cout << nums;
        int n = nums.size();
        int p = 0, q = 0;
        int r = 0;
        for (; q < n; ++q) {
            if (nums[p] != nums[q]) {
                p = q;
                nums[r++] = nums[q];
                continue;
            }
            if (q - p < 2) {
                nums[r++] = nums[q];
            }
        }
        cout << nums;
        return r;
    }
};

TEST_CASE("Remove Duplicates from Sorted Array II - Example 1") {
    vector<int> nums{1, 1, 1, 2, 2, 3};
    vector<int> output{1, 1, 2, 2, 3};
    int answer = Solution().removeDuplicates(nums);
    REQUIRE(answer == 5);
    REQUIRE(vector<int>(nums.begin(), nums.begin() + output.size()) == output);
}

TEST_CASE("Remove Duplicates from Sorted Array II - Example 2") {
    vector<int> nums{0, 0, 1, 1, 1, 1, 2, 3, 3};
    vector<int> output{0, 0, 1, 1, 2, 3, 3};
    int answer = Solution().removeDuplicates(nums);
    REQUIRE(answer == 7);
    REQUIRE(vector<int>(nums.begin(), nums.begin() + output.size()) == output);
}

TEST_CASE("Remove Duplicates from Sorted Array II - Empty") {
    vector<int> nums{};
    vector<int> output{};
    int answer = Solution().removeDuplicates(nums);
    REQUIRE(answer == 0);
    REQUIRE(vector<int>(nums.begin(), nums.begin() + output.size()) == output);
}

TEST_CASE("Remove Duplicates from Sorted Array II - Single") {
    vector<int> nums{1};
    vector<int> output{1};
    int answer = Solution().removeDuplicates(nums);
    REQUIRE(answer == 1);
    REQUIRE(vector<int>(nums.begin(), nums.begin() + output.size()) == output);
}
