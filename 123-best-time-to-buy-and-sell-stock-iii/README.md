## [Best Time to Buy and Sell Stock III](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)

答案中最快的算法，采用动态规划，且相当巧妙，可以求解任意transaction的最大profit，如下：

```c++
int maxProfit(const vector<int> &prices) {
    int n = prices.size();
    if (n <= 1)
        return 0;
    int K = 2;
    int dp[K + 1][n];
    memset(dp, 0, sizeof(dp));
    for (int k = 1; k <= K; k++) {
        int minPrice = prices[0];
        for (int i = 1; i < n; i++) {
            minPrice = min(minPrice, prices[i] - dp[k - 1][i - 1]); // *1
            dp[k][i] = max(dp[k][i - 1], prices[i] - minPrice); // *2
        }
    }
    return dp[K][n - 1];
}
```

重点在于1处求解最小值。试解释如下：
``dp[k][i]``表示``prices[0..i]``数组进行k次transaction的最大收益，因此``dp[0][i]``恒为0。

对于``k,i``，minPrice的含义为，为``0...i``中这样一个元素j，``0<=j<=i``，使得``prices[i]-prices[j]+dp[k-1][j-1]``最大，这样就包含了``prices[i]-prices[j]``一次和``dp[k-1][j-1]``k-1次transaction，共k次的最大值。

因此，如果``prices[i]-dp[k-1][i-1]<minPrice``，就可以保证后续的任意s，``i<=s<n``，有``prices[s]-(prices[i]-dp[k-1][i-1])>prices[s]-minPrice``，从而需要1处的赋值。

简要：i可以作为minPrice的含义，为可以作为第k次transaction的买入点，使得0到i-1中进行k-1次transaction，i为第k次的买入点时，总k次transaction最大。
