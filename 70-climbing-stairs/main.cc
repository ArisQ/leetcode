#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        if (n <= 2)
            return n; // 1--1   2--2
        vector<int> steps(n, 0);
        steps[0] = 1;
        steps[1] = 2;
        for (int i = 2; i < n; ++i)
            steps[i] = steps[i - 1] + steps[i - 2];
        return steps[n - 1];
    }
};

TEST_CASE("Climbing Stairs") {
    REQUIRE(Solution().climbStairs(2) == 2);
    REQUIRE(Solution().climbStairs(3) == 3);
}
