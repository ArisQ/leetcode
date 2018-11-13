#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int> &nums) {
        vector<vector<int>> result;
        if (nums.empty())
            return result;
        quickSort(nums, nums.begin(), nums.end());
        vector<int> neg_value;
        vector<int> neg_count;
        vector<int> pos_value;
        vector<int> pos_count;
        neg_value.reserve(nums.size());
        neg_count.reserve(nums.size());
        pos_value.reserve(nums.size());
        pos_count.reserve(nums.size());
        auto iter = nums.begin();
        int pre = *iter - 1;
        int index = -1;
        for (; iter != nums.end() && *iter < 0; ++iter) {
            if (*iter == pre)
                ++neg_count[index];
            else {
                neg_value.push_back(*iter);
                neg_count.push_back(1);
                pre = *iter;
                ++index;
            }
        }
        size_t zero_count = 0;
        while (*iter == 0) {
            ++zero_count;
            ++iter;
        }
        if (iter != nums.end()) {
            pre = *iter - 1;
            index = -1;
        }
        for (; iter != nums.end(); ++iter) {
            if (*iter == pre)
                ++pos_count[index];
            else {
                pos_value.push_back(*iter);
                pos_count.push_back(1);
                pre = *iter;
                ++index;
            }
        }
        if (zero_count >= 3)
            result.push_back({0, 0, 0});
        if (zero_count > 0) {
            // -a 0 a
            auto pos_iter = pos_value.cbegin();
            auto neg_iter = neg_value.crbegin();
            while (pos_iter != pos_value.cend() && neg_iter != neg_value.crend()) {
                if (*pos_iter + *neg_iter == 0) {
                    result.push_back({*neg_iter, 0, *pos_iter});
                    ++pos_iter;
                    ++neg_iter;
                } else if (*pos_iter + *neg_iter > 0)
                    ++neg_iter;
                else
                    ++pos_iter;
            }
        }
        //-a b c or -a -b c
        //
        return result;
    }

    void quickSort(vector<int> &nums, vector<int>::iterator begin, vector<int>::iterator end) {
        if (begin == end || begin + 1 == end)
            return;
        auto p = begin;
        int tmp;
        for (auto i = begin + 1; i != end; ++i) {
            if (*i < *p) {
                tmp = *i;
                *i = *(p + 1);
                *(p + 1) = *p;
                *p = tmp;
            }
        }
        quickSort(nums, begin, p);
        quickSort(nums, p + 1, end);
    }
};

TEST_CASE("Longest common prefix") {
    vector<int> input = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> output = {
        {-1, 0,  1},
        {-1, -1, 2},
    };
    REQUIRE(Solution().threeSum(input) == output);
}
