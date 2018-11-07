## [Container with most water](https://leetcode.com/problems/container-with-most-water/)

1. 基础解法

    共$n$条线，有$(n-1)^2/2$种不同的情况，最简单的方法是两层循环，判断最大容量。时间复杂度为$O(n^2)$

    ```c++
    int maxArea(vector<int> &height)
    {
        int result = 0;
        int cij = 0;
        for (size_t i = 0; i < height.size(); ++i)
            for (size_t j = i + 1; j < height.size(); ++j) {
                cij = (j - i) * (height[i] <= height[j] ? height[i] : height[j]);
                if (cij > result)
                    result = cij;
            }
        return result;
    }
    ```

    提交以后只排到10%，确实很低

2. 跳过不必要的计算

    对于以$i$为起始的container，若$a_j>a_i$，则$\forall k \in (i,j)$，以$i,k$为边的container的容量都小于以$i,j$为边的container。

    证明：$(j-i)*min(a_i,a_j)>(k-i)*a_i>(k-i)*min(a_i,a_k)$

    因此，从尾部往前计算，遇到$j$使得$a_j>a_i$即可停止循环，如下：

    ```c++
    int maxArea(vector<int> &height)
    {
        int result = 0;
        int cij = 0;
        size_t size = height.size();
        for (size_t i = 0; i < size; ++i)
            for (size_t j = size - 1; j > i; --j) {
                if (height[j] >= height[i]) {
                    cij = (j - i) * height[i];
                    if (cij > result)
                        result = cij;
                    break;
                } else {
                    cij = (j - i) * height[j];
                    if (cij > result)
                        result = cij;
                }
            }
        return result;
    }
    ```

    **[错误分析]**
    考虑算法的平均时间复杂度，对于$\forall j \in [0,n)$，$a_j>a_i$的概率为0.5，因此，内层循环运行k次（即k满足$a_{n-k}>a_i \And \forall n-k<l<n, a_l<a_i$）结束的概率为$0.5^k$。因此，内层循环次数的数学期望是（考虑到$\forall j>i, a_j<a_i$时的次数也为$n-i-1$）
    $$
    (n-i-1)*0.5^{n-i-1}+\sum_{k=1}^{n-i-1} 0.5^k \cdot k =2-0.5^{n-i-2}=O(1)
    $$
    因此，平均时间复杂度为
    $$O(\sum_{i=0}^{n-1} O(1))=O(n)$$
    **有误，对于$k$个数，$b_1,b_2,\cdots,b_k$，$b_1<b_j (\forall j\in\{2,3,\cdots,k\})$的概率为$1/k$（即$b_1$最小的概率），而不应是$0.5^{k-1}$**

    重新分析，对于以$i$为起点的container，可以假设$a_i,a_{i+1},\cdots,a_{n-1}$大小随机平均分布。设内层循环运行$k$次的概率$p_i(k)$，

    当$k=1$时，$p_i(1)=p(a_{n-1}>=a_i)=0.5$；

    当$k=2$时，$p_i(2)=p(a_{n-2}>=a_i \And a_{n-1}<a_i)=\frac{1}{3*2}$，即在$a_i,a_{n-2},a_{n-1}$三个数中，$a_{n-2}$最大，$a_i$其次，$a_{n-1}$最小；

    当$k=3$时，$p_i(3)=p(a_{n-3}>=a_i \And a_{n-2}<a_i \And a_{n-1}<a_i)=\frac{1}{4*3}$，即在$a_i,a_{n-3},a_{n-2},a_{n-1}$四个数中，$a_{n-3}$最大，$a_i$其次，$a_{n-2},a_{n-1}$两者为其余；

    当$k=n-i-1$有两种情况时，一是在$a_i,a_{i+1},\cdots,a_{n-1}$中$a_i$最大，二是$a_{i+1}$最大，$a_i$其次。因此，
    $p_i(n-i-1)=p(a_{i+1}<a_i \And \cdots \And a_{n-2}<a_i \And a_{n-1}<a_i)+p(a_{i+1}>=a_i \And a_{i+2}<a_i \And \cdots \And a_{n-2}<a_i \And a_{n-1}<a_i)=\frac{1}{n-i-1}+\frac{1}{(n-i-1)(n-i-2)}$，

    综上，对于$k=n-i-1$有
    $$p_i(n-i-1)=\frac{1}{n-i-1}+\frac{1}{(n-i-1)(n-i-2)}$$
    对于$0<k<n-i-1$有
    $$p_i(k)=\frac{1}{(k+1)k}$$

    则对于以$i$为起始,内层循环运行次数的数学期望为
    $$
    \sum_{k=1}^{n-i-1} {k \cdot p_i(k)}
    = \sum_{k=1}^{n-i-1} k\frac{1}{(k+1)k} + (n-i-1)\frac{1}{n-i-1}
    = 1+\sum_{k=1}^{n-i-1} \frac{1}{k+1}
    = O(\lg n)
    $$

    因此，平均时间复杂度为
    $$O(\sum_{i=0}^{n-1} O(\lg n))=O(n \lg n)$$

    提交后约27%，还是没有达到平均水平，应该是存在$O(n)$的解法）。
