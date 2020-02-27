## [Single Number II](https://leetcode.com/problems/single-number-ii/)

* 方法1同136题，随机选择然后分隔，平均复杂度O(n)，常数空间，8ms(98.43%)，空间10MB(12.5%)

* 答案中的位运算方法，大体思想如下，每bit独立计，并且保存该位出现过1次或者2次，然后不断迭代。