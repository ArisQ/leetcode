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
    vector<vector<int>> merge(vector<vector<int>> &intervals) {
        vector<vector<int>> result;
        if (intervals.empty())
            return result;
        sort(intervals.begin(), intervals.end(), [](vector<int> &a, vector<int> &b) {
            return a[0] < b[0];
        });
        int min = intervals[0][0];
        int max = intervals[0][1];
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] <= max) {
                max = intervals[i][1] > max ? intervals[i][1] : max;
                continue;
            } else {
                result.push_back(vector<int>{min, max});
                min = intervals[i][0];
                max = intervals[i][1];
            }
        }
        result.push_back(vector<int>{min, max});
        return result;
    }
};

TEST_CASE("Merge Intervals - Example 1") {
    vector<vector<int>> input{
        {1,  3},
        {2,  6},
        {8,  10},
        {15, 18}
    };
    vector<vector<int>> output{
        {1,  6},
        {8,  10},
        {15, 18}
    };
    REQUIRE(Solution().merge(input) == output);
}

TEST_CASE("Merge Intervals - Example 2") {
    vector<vector<int>> input{
        {1, 4},
        {4, 5}
    };
    vector<vector<int>> output{
        {1, 5}
    };
    REQUIRE(Solution().merge(input) == output);
}

TEST_CASE("Merge Intervals - Wrong Answer 1") {
    vector<vector<int>> input{
        {1, 4},
        {2, 3}
    };
    vector<vector<int>> output{
        {1, 4}
    };
    REQUIRE(Solution().merge(input) == output);
}

