## [Palindrome Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii/)

### 方法一

子字符串s[i,j)的最小拆分方法，要么为0（自身为回文，此时通过判断s[i+1,j-1)为回文且s[i]==s[j-1]），要么可以拆分为s[i,l)和s[l,j)；因此只要构造关于s[i,j)的最小拆分表，并从长度最小的开始计算即可。


|      | 0    | 1          | 2          | ...  | n-1        | n            |
| ---- | ---- | ---------- | ---------- | ---- | ---------- | ------------ |
| 0    |      | `s[0,1)=0` | `s[0,2)`   | ...  | `s[0,n-1)` | `s[0,n)`     |
| 1    |      |            | `s[1,2)=0` | ...  | `s[1,n-1)` | `s[1,n)`     |
| 2    |      |            |            | ...  | `s[2,n-1)` | `s[2,n)`     |
| ...  | ...  | ...        | ...        | ...  | ...        | ...          |
| n-1  |      |            |            | ...  |            | `s[n-1,n)=0` |
| n    |      |            |            | ...  |            |              |

时间为$O(n^3)$，在长字符串时报了Time Limit Exceeded

### 方法二

建立以i为起点的所有回文终点的索引，即``vector<vector<int>> ends(n)``，则``s[i,ends[i][j]]``为回文。

因此，建立了0...n之间的路径，只要找到0到n的最短路径即可，采用BFS

复杂度$O(n^2)$

### leetcode最优解解析

代码如下，简洁报销
```c++
int minCut(string s) {
    int n = s.size();
    vector<int> cut(n+1, 0);  // number of cuts for the first k characters
    for (int i = 0; i <= n; i++) cut[i] = i-1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; i-j >= 0 && i+j < n && s[i-j]==s[i+j] ; j++) // odd length palindrome
            cut[i+j+1] = min(cut[i+j+1],1+cut[i-j]);

        for (int j = 1; i-j+1 >= 0 && i+j < n && s[i-j+1] == s[i+j]; j++) // even length palindrome
            cut[i+j+1] = min(cut[i+j+1],1+cut[i-j+1]);
    }
    return cut[n];
}
```

跟第一种方法类似，但注意到不管如何分都需要从0开始，因此可以拆分为从0开始的若干拆分和以i结尾的最后一个拆分。假设已知0...i-1的最少拆分，只要找到以i结束的所有回文并取所有回文剩下的字符串的最少拆分的最小值并加一即可。

同时采用了一个技巧，即最后一个拆分不是以i结尾，而是以i为中心或i-1/2为中心，这样在找所有回文时就可以逐渐递增，而不是每次都要判断子字符串是否是回文（结尾的话其实需要判断以i结尾的所有字符串，太麻烦，而中心，则如果短字符串不是则长的不用判断，肯定不是）。

