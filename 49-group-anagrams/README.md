## [Group Anagrams](https://leetcode.com/problems/group-anagrams/)

解法以int[26]，每个字母出现的次数作为key，进行比较。最快答案中将字符串按字母排序后作为key，进行比较。

对于字符串都比较长的情况出现次数为key（$O(n)$）可能比排序后的字符串为key（$O(n log{n})$）要快，但测试用例中应该以短字符串为主，因此以排序后的字符串为key会较快。

