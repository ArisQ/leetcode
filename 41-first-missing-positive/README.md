## [First Missing Positive](https://leetcode.com/problems/first-missing-positive/)

解法中用了sort，因此不是很满意，但是题目并没有规定，而且sort实现一般为$O(\log{n})$，因此能够满足要求。

然后，学习了其他人的解法，比较迷的是运行时间0ms的最快解法，如下：

```c++
int firstMissingPositive(vector<int>& nums) {
    if (nums.empty())
        return 1;
    for (int i = 0; i < nums.size(); i++) {
        int index = i + 1;
        while (nums[i] != i + 1) {
            if (index == nums.size())
                return i + 1;
            swap(nums[i], nums[index++]);
        }
    }
    return nums.size() + 1;
}
```

这个解法最坏情况下是$O(n^2)$的，不满足题目要求，然而运行时间居然最短，不知道测试用例怎么写的。以$[20,19,18,...,3,2,1]$测试时，内层while循环达到190次，正好符合$n(n-1)/2=20*19/2=190$。

一个比较好的解法如下：

```c++
int firstMissingPositive(vector<int>& nums) {
    int count = 0;
    int n = nums.size();

    int i = 0;
    while (i < n) {
        cout << "[" << count++ << "," << i << "] " << nums;
        if (nums[i] >= 1 && nums[i] <= n && nums[i] != nums[nums[i] - 1])
            swap(nums[i], nums[nums[i] - 1]);
        else i++;
    }

    for (int i = 0; i < n; i++) {
        if (nums[i] != i + 1) return i + 1;
    }

    return n + 1;
}
```

最核心也最懂的地方是``if (nums[i] >= 1 && nums[i] <= n && nums[i] != nums[nums[i] - 1]) swap(nums[i], nums[nums[i] - 1]);``，但理解了基本思想后也很简单。

就是将1,2,3,...,n填充到数组对应的地方，从前向后，找到一个数``nums[i]``以后，如果这个数所应该在的位置不是这个数，那么把找到的数交换过去。

因为在原数组交换所以会比较难懂，如果构造一个新的数组，然后对于``nums[i]``，则将新数组的``nums[i]``位置设为True或者``nums[i]``进行标记，则容易理解一些。

如果找到的数所应该在的位置已经是这个数，那么不需要交换，因此最多交换n次，而i增长也是n次，因此最多2n次，因此是$O(n)$的。

