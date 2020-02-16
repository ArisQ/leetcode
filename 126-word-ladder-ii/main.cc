#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <queue>

using namespace std;

class Solution {
public:
    bool isNear(const string &a, const string &b) {
        int diff = 0;
        int n = a.size();
        for (int i = 0; i < n; ++i)
            if (a[i] != b[i]) {
                ++diff;
                if (diff > 1)
                    return false;
            }
        return diff == 1;
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, const vector<string> &wordList) {
        vector<vector<string>> result;
        int n = wordList.size();
        vector<vector<int>> near(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < i; ++j) {
                if (isNear(wordList[i], wordList[j])) {
                    near[i].push_back(j);
                    near[j].push_back(i);
                }
            }
        int b = -1, e = -1;
        for (int i = 0; i < n; ++i) {
            if (endWord == wordList[i]) e = i;
            if (beginWord == wordList[i]) b = i;
        }
        if (e == -1) return result;
        vector<int> steps(n, -1);
        vector<vector<int>> pre(n);
        queue<int> curLevel;
        if (b != -1) {
            steps[b] = 0;
            curLevel.push(b);
        } else {
            for (int i = 0; i < n; ++i)
                if (isNear(beginWord, wordList[i])) {
                    steps[i] = 1;
                    curLevel.push(i);
                }
        }
        curLevel.push(-1);
        bool found = false;
        while (!curLevel.empty()) {
            int f = curLevel.front();
            curLevel.pop();
            if (f == -1) {
                if (curLevel.empty()) break;
                if (found) break;
                curLevel.push(-1);
                continue;
            }
            for (int i = 0; i < near[f].size(); ++i) {
                if (steps[near[f][i]] == -1) {
                    steps[near[f][i]] = steps[f] + 1;
                    pre[near[f][i]].push_back(f);
                    curLevel.push(near[f][i]);
                } else if (steps[near[f][i]] == steps[f] + 1) {
                    pre[near[f][i]].push_back(f);
                } // 否则不是最短路径
                if (near[f][i] == e)
                    found = true;
            }
        }
        // 构造结果集
        vector<string> path;
        path.push_back(endWord);
        constructLadder(beginWord, wordList, steps, pre, path, result, e);
        return result;
    }

    void constructLadder(const string &beginWord,
                         const vector<string> &wordList,
                         const vector<int> &steps,
                         const vector<vector<int>> &pre,
                         vector<string> &path,
                         vector<vector<string>> &result,
                         int cur) {
        if (steps[cur] == 1) {
            path.push_back(beginWord);
            result.emplace_back(path.crbegin(), path.crend());
            path.pop_back();
            return;
        }
        int choices = pre[cur].size();
        for (int i = 0; i < choices; ++i) {
            path.push_back(wordList[pre[cur][i]]);
            constructLadder(beginWord, wordList, steps, pre, path, result, pre[cur][i]);
            path.pop_back();
        }
    }
};

TEST_CASE("Word Ladder II") {
    REQUIRE(Solution().findLadders("hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}) == vector<vector<string>>{
        {"hit", "hot", "dot", "dog", "cog"},
        {"hit", "hot", "lot", "log", "cog"}
    });
    REQUIRE(Solution().findLadders("hit", "cog", {"hot", "dot", "dog", "lot", "log"}) == vector<vector<string>>{});
}
