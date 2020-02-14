#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    bool isNear(const string &a, const string &b) {
        int diff = 0;
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) {
                ++diff;
                if (diff > 1)
                    return false;
            }
        }
        return diff == 1;
    }

    int ladderLength(string beginWord, string endWord, const vector<string> &wordList) {
        int n = wordList.size();
        vector<vector<int>> near(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < i; j++) {
                if (isNear(wordList[i], wordList[j])) {
                    near[i].push_back(j);
                    near[j].push_back(i);
                }
            }
        int b = -1, e = -1;
        for (int i = 0; i < n; ++i) {
            if (wordList[i] == endWord) {
                e = i;
            }
            if (wordList[i] == beginWord) {
                b = i;
            }
        }
        if (e == -1) return 0;
        vector<bool> accessed(n);
        queue<int> level;
        int result;
        if (b == -1) {
            for (int i = 0; i < n; ++i) {
                if (isNear(beginWord, wordList[i])) {
                    level.push(i);
                    accessed[i] = true;
                    if (e == i) return 2;
                }
            }
            result = 2;
        } else {
            accessed[b] = true;
            level.push(b);
            result = 1;
        }
        level.push(-1);
        while (!level.empty()) {
            int front = level.front();
            level.pop();
            if (front == -1) {
                if (level.empty())
                    break;
                level.push(-1);
                ++result;
                continue;
            }
            for (int i = 0; i < near[front].size(); ++i) {
                if (accessed[near[front][i]]) {
                    continue;
                }
                if (near[front][i] == e)
                    return result + 1;
                level.push(near[front][i]);
                accessed[near[front][i]] = true;
            }
        }
        return 0;
    }
};

TEST_CASE("Word Ladder") {
    REQUIRE(Solution().ladderLength("hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}) == 5);
    REQUIRE(Solution().ladderLength("hit", "cog", {"hot", "dot", "dog", "lot", "log"}) == 0);
    REQUIRE(Solution().ladderLength("a", "c", {"a", "b", "c"}) == 2);
    REQUIRE(Solution().ladderLength("hot", "dog", {"hot","dog"}) == 0);
}
