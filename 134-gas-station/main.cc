#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
    inline int next(int i, int n) {
        return (i + 1) % n;
    }
    inline int previous(int i, int n) {
        return i >= 1 ? i - 1 : n - 1;
    }
public:
    int canCompleteCircuit(const vector<int> &gas, const vector<int> &cost) {
        int n = gas.size(); //n>0
        if (n == 1) return gas[0] >= cost[0] ? 0 : -1;
        int s = 0, e = 1;
        int g = gas[0] - cost[0];
        while (s != e) {
            if (g >= 0) {
                g += gas[e] - cost[e];
                e = next(e, n);
            } else {
                s = previous(s, n);
                g += gas[s] - cost[s];
            }
        }
        return g >= 0 ? s : -1;
    }
};

TEST_CASE("Gas Station") {
    REQUIRE(Solution().canCompleteCircuit({1, 2, 3, 4, 5}, {3, 4, 5, 1, 2}) == 3);
    REQUIRE(Solution().canCompleteCircuit({2, 3, 4}, {3, 4, 3}) == -1);
    REQUIRE(Solution().canCompleteCircuit({4}, {5}) == -1);
}
