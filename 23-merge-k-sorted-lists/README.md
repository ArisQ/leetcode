## [Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)

假设公有k个List，平均每个List有m个元素，则有以下思路。

1. 依次挑选最小元素

同Merge Two Sorted Lists思路，每次从k个List中选择最小的一个元素。每次需要比较k-1次，最坏情况需要选择所有元素，共需$k\*m$次，故时间复杂度为$O(k^2*m)$

2. 每次合并两个List，依次合并

设List为$l_1,l_2,...,l_n$，依次合并为$l^{'}_1,l_3,...,l_n$，$l^{''}_1,l_4,...,l_n$，...，$l^{n-1}_1$。

每次合并$l_i,l_j$时，时间复杂度为$O(m_i+m_j)$，其中$m_i$为List i的元素个数，故总复杂度为$O(k\*m_1+(k-1)\*m_2+...+2\*m_{k-1}+m_k) = O(\frac{k\*(k-1)}{2} \* m) = O(k^2*m)$，与思路1相同，常量系数是思路1的一半。

3. 两两合并，递归

先将k个List两两合并，得到k/2个List，再递归合并k/2个List。

每次递归，都需要$O{m_1+m_2+...+m_k}$，需要递归$lg{2}{k}$次，故时间复杂度为${k\*lg(k)\*m}。

在实现时可以用队列实现，将k个List看成队列，每次取出头部两个List，合并后放入队列尾部，直到队列中只包含一个List为止。





