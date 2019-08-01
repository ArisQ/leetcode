#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval) {
        int interval_size = intervals.size();
        int min_overlapped_index = interval_size;
        int max_overlapped_index = -1;
        auto insert_position = intervals.begin();
        for (int i = 0; i < intervals.size(); ++i) {
            if (intervals[i][1] >= newInterval[0] && intervals[i][0] <= newInterval[1]) {
                //overlapped
                if (i < min_overlapped_index)
                    min_overlapped_index = i;
                if (i > max_overlapped_index)
                    max_overlapped_index = i;
            } else {
                if (intervals[i][0] < newInterval[0])
                    ++insert_position;
            }
        }
        if (max_overlapped_index == -1) {
            intervals.insert(insert_position, newInterval);
            return intervals;
        }
        vector<vector<int>> result;
        result.reserve(interval_size - (max_overlapped_index - min_overlapped_index));
//        cout << min_overlapped_index << " " << max_overlapped_index << endl;
        for (int i = 0; i < min_overlapped_index; ++i)
            result.push_back(intervals[i]);
        result.push_back(vector<int>{
            min(intervals[min_overlapped_index][0], newInterval[0]),
            max(intervals[max_overlapped_index][1], newInterval[1])
        });
        for (int i = max_overlapped_index + 1; i < interval_size; ++i)
            result.push_back(intervals[i]);
        return result;
    }
};

TEST_CASE("Insert Interval - Example 1") {
    vector<vector<int>> input{
        {1, 3},
        {6, 9}
    };
    vector<int> newInterval = {2, 5};
    vector<vector<int>> output{
        {1, 5},
        {6, 9}
    };
    REQUIRE(Solution().insert(input, newInterval) == output);
}

TEST_CASE("Insert Interval - Example 2") {
    vector<vector<int>> input{
        {1,  2},
        {3,  5},
        {6,  7},
        {8,  10},
        {12, 16}
    };
    vector<int> newInterval = {4, 8};
    vector<vector<int>> output{
        {1,  2},
        {3,  10},
        {12, 16}
    };
    REQUIRE(Solution().insert(input, newInterval) == output);
}

TEST_CASE("Insert Interval - Wrong Answer 1") {
    vector<vector<int>> input{
        {1, 5}
    };
    vector<int> newInterval = {0, 0};
    vector<vector<int>> output{
        {0, 0},
        {1, 5}
    };
    REQUIRE(Solution().insert(input, newInterval) == output);
}
