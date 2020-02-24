## [Gas Station](https://leetcode.com/problems/gas-station/)

想法很简单，选定从s-e，如果剩余gas不小于0，则继续前往下一站，如果小于0，则需要将起点s向前修改，直到到达e是gas大于0。当s==e时结束，如果此时gas大于0则成功，否则返回-1。时间复杂度O(n)，且每个station只访问一次。

PS: 指定inline并没有用，会导致Runtime提高，不如直接写表达式