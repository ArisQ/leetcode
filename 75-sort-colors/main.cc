#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    void sortColors(vector<int> &nums) {
        int numsLen = nums.size();
        int r = 0, w = 0, b = 0;
        for (int i = 0; i < numsLen; ++i) {
            switch (nums[i]) {
                case 0:
                    nums[b++] = 2;
                    nums[w++] = 1;
                    nums[r++] = 0;
                    break;
                case 1:
                    nums[b++] = 2;
                    nums[w++] = 1;
                    break;
                case 2:
                    ++b;
                    break;
                default:
                    return;
            }
        }
    }
};

TEST_CASE("Sort Colors") {
    vector<int> input{2, 0, 2, 1, 1, 0};
    vector<int> output{0, 0, 1, 1, 2, 2};
    Solution().sortColors(input);
    REQUIRE(input == output);
}
