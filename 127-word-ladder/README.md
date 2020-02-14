## [Word Ladder](https://leetcode.com/problems/word-ladder/)

因为有被问到中等题目的解题实际，特意统计了下，本题58分钟，去除中间下楼拿东西，差不多48分钟，还是太乐观了。

思路为建立单词之间的transform图，然后通过广度优先搜索，找到最短路径，但wordList按字典排序，所有应该有更便捷的方法，但解题的时候没有细想。

看Solution，可以用双向BFS
