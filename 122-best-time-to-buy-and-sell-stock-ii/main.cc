#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    int maxProfit(const vector<int> &prices) {
        int profit = 0;
        int n = prices.size();
        if (n < 2)
            return profit;
        int min = prices[0];
        int previous = prices[0];
        for (int i = 1; i < n; ++i) {
            if (prices[i] < previous) {
                profit += previous - min;
                min = prices[i];
                previous = prices[i];
            } else { //prices[i]>=previous
                previous = prices[i];
            }
        }
        profit += previous - min;
        return profit;
    }
};

TEST_CASE("Best Time to Buy and Sell Stock II") {
    REQUIRE(Solution().maxProfit({7, 1, 5, 3, 6, 4}) == 7);
    REQUIRE(Solution().maxProfit({1, 2, 3, 4, 5}) == 4);
    REQUIRE(Solution().maxProfit({7, 6, 4, 3, 1}) == 0);
}
