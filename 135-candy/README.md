## [Candy](https://leetcode.com/problems/candy/)

### 方法1

通过candies数组保存每个child分到的数量，循环，保证$0,...,i-1$取最小值，则对于$i$，如果$ratings[i]>ratings[i-1]$则取$candies[i]=candies[i-1]+1$，否则取$candies[i]=1$，并且从i向0回溯，解决所有$j \in {i,i-1,...,1}$，但$ratings[j]<ratings[j-1] && candies[j]>candies[j-1]$的问题

最差时间复杂度为$O(n^2)$

### 方法2

根据方法1，并不需要维护所有child的candy，只需处理以下情况

* $ratings[i]==ratings[i-1]$
i和i-1没有约束关系，$candies[i]=1$即可


* $ratings[i]>ratings[i-1]$
$candies[i]=candies[i-1]+1$即可，不会破坏约束

* $ratings[i]<ratings[i-1]$
$candies[i]=1$，会破坏约束，但可以这样假设
存在最近的$peak \in {0,1,...,i-1}$，使得$ratings[peak-1]<=ratings[peak]>=ratings[peak+1]$，且可知$peak, peak+1, ... , i$是递减的，则$candies[peak+1]=i-peak-1, ..., candies[i-2]=2,candies[i-1]=1$，因为$peak+1, ... , i-2, i-1$都是通过$ratings[i]<ratings[i-1]$建立起来的

而$candies[peak]$可能受到其左边的约束，而大于$i-peak$

因此，只需要在迭代时记录peak_index和peak_value，对$peak+1, ..., i-1$都加1，通过判断peak_value决定是否需要对peak位置加1，即可解决冲突。（包括i，则总sum，加i-peak_index或则为加i-peak_index+1）

peak_index位置值的增加不受约束


