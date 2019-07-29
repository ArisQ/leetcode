#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
        vector<int> selected;
        vector<vector<int>> result;
        sort(candidates.begin(), candidates.end());
        combinationSum2(candidates.begin(), candidates.end(), result, selected, target);
        return result;
    }

    void combinationSum2(vector<int>::iterator begin,
                        vector<int>::iterator end,
                        vector<vector<int>> &result,
                        vector<int> &selected,
                        int target) {
        if (begin == end || *begin > target)
            return;
        if (*begin == target) {
            selected.push_back(*begin);
            result.push_back(selected);
            selected.pop_back();
            return;
        }
        // *begin < target
        selected.push_back(*begin);
        combinationSum2(begin + 1, end, result, selected, target - *begin);
        selected.pop_back();
        while (begin + 1 != end && *begin == *(begin + 1))
            ++begin;
        combinationSum2(begin + 1, end, result, selected, target);
    }
};


multiset<multiset<int>> vector_to_mutliset(vector<vector<int>> v) {
    multiset<multiset<int>> result;
    for (auto &e:v)
        result.emplace(multiset<int>{e.begin(), e.end()});
    return result;
}

TEST_CASE("Combination Sum II - Example 1") {
    int target = 8;
    vector<int> candidates{10, 1, 2, 7, 6, 1, 5};
    vector<vector<int>> output{
            {1, 7},
            {1, 2, 5},
            {2, 6},
            {1, 1, 6}
    };
    auto answer = Solution().combinationSum2(candidates, target);
    REQUIRE(vector_to_mutliset(output) == vector_to_mutliset(answer));
}

TEST_CASE("Combination Sum II - Example 2") {
    int target = 5;
    vector<int> candidates{2, 5, 2, 1, 2};
    vector<vector<int>> output{
            {1, 2, 2},
            {5}
    };
    auto answer = Solution().combinationSum2(candidates, target);
    REQUIRE(vector_to_mutliset(output) == vector_to_mutliset(answer));
}
