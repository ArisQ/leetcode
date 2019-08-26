#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int pricesSize = prices.size();
        if (pricesSize < 2)
            return 0;
        int result = 0;
        int min = prices[0];
        for (int i = 1; i < pricesSize; ++i) {
            if (prices[i] - min > result)
                result = prices[i] - min;
            else if (prices[i] < min)
                min = prices[i];
        }
        return result;
    }
};

TEST_CASE("Best Time to Buy and Sell Stock - Example 1") {
    vector<int> input{7, 1, 5, 3, 6, 4};
    REQUIRE(Solution().maxProfit(input) == 5);
}

TEST_CASE("Best Time to Buy and Sell Stock - Example 2") {
    vector<int> input{7, 6, 4, 3, 1};
    REQUIRE(Solution().maxProfit(input) == 0);
}
