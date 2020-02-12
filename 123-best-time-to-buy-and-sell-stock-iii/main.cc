#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    int maxProfit(const vector<int> &prices) {
        int n = prices.size();
        if (n < 2)
            return 0;
        vector<int> firstPart(n);
        int profit;
        int maxProfit = 0;
        int minPrice = prices[0];
        for (int i = 1; i < n; ++i) {
            if (prices[i] < minPrice)
                minPrice = prices[i];
            profit = prices[i] - minPrice;
            if (profit > maxProfit)
                maxProfit = profit;
            firstPart[i] = maxProfit;
        }
        int totalMaxProfit = firstPart[n - 1]; //只有一次transaction的最大profit
        int maxPrice = prices[n - 1];
        for (int i = n - 2; i > 0; --i) {
            if (prices[i] > maxPrice)
                maxPrice = prices[i];
            profit = maxPrice - prices[i] + firstPart[i - 1];
            if (profit > totalMaxProfit)
                totalMaxProfit = profit;
        }
        return totalMaxProfit;
    }
};

TEST_CASE("Best Time to Buy and Sell Stock III") {
    REQUIRE(Solution().maxProfit({3, 3, 5, 0, 0, 3, 1, 4}) == 6);
    REQUIRE(Solution().maxProfit({1, 2, 3, 4, 5}) == 4);
    REQUIRE(Solution().maxProfit({7, 6, 4, 3, 1}) == 0);
}


