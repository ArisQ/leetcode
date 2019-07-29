#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

template<typename T>
void printByIter(T begin, T end) {
    for (T iter = begin; iter != end; ++iter)
        cout << *iter << " ";
    cout << endl;
}

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end());
        return combinationSum(candidates.begin(), candidates.end(), target);
    }

    vector<vector<int>> combinationSum(vector<int>::iterator begin,
                                       vector<int>::iterator end,
                                       int target) {
        vector<vector<int>> result;
        if (begin == end || *begin > target)
            return result;
        if (*begin == target) {
            result.emplace_back(vector<int>{*begin});
            return result;
        }
        // *begin < target
        result = combinationSum(begin, end, target - *begin);
        for (auto &c:result) {
            c.push_back(*begin);
        }
        auto without_current = combinationSum(begin + 1, end, target);
        for (auto &c:without_current)
            result.emplace_back(c);
        return result;
    }
};


multiset<multiset<int>> vector_to_mutliset(vector<vector<int>> v) {
    multiset<multiset<int>> result;
    for (auto &e:v)
        result.emplace(multiset<int>{e.begin(), e.end()});
    return result;
}

TEST_CASE("Combination Sum - Example 1") {
    int target = 7;
    vector<int> candidates{2, 3, 6, 7};
    vector<vector<int>> output{
            {7},
            {2, 2, 3},
    };
    auto answer = Solution().combinationSum(candidates, target);
    REQUIRE(vector_to_mutliset(output) == vector_to_mutliset(answer));
}

TEST_CASE("Combination Sum - Example 2") {
    int target = 8;
    vector<int> candidates{2, 3, 5};
    vector<vector<int>> output{
            {2, 2, 2, 2},
            {2, 3, 3},
            {3, 5}
    };
    auto answer = Solution().combinationSum(candidates, target);
    REQUIRE(vector_to_mutliset(output) == vector_to_mutliset(answer));
}
