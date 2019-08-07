#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <queue>

using namespace std;

class Solution {
public:
    struct OperationState {
        int word1Index;
        int word2Index;
        int operations;
    };

    /* 广度有限搜索，选取三种操作，直到两个单词相等 */
    int minDistance(string word1, string word2) {
        int word1Len = word1.size();
        int word2Len = word2.size();
        queue<OperationState> stateQueue;
        stateQueue.push({0, 0, 0});
        while (!stateQueue.empty()) {
            const OperationState &state = stateQueue.front();
            int index1 = state.word1Index;
            int index2 = state.word2Index;
            int operations = state.operations;
            stateQueue.pop();
            while (index1 != word1Len && index2 != word2Len && word1[index1] == word2[index2]) {
                ++index1;
                ++index2;
            }
            if (index1 == word1Len && index2 == word2Len)
                return operations;
            if (index1 == word1Len) {
                stateQueue.push({index1, index2 + 1, operations + 1});
                continue;
            }
            if (index2 == word2Len) {
                stateQueue.push({index1 + 1, index2, operations + 1});
                continue;
            }
            stateQueue.push({index1, index2 + 1, operations + 1}); //insert
            stateQueue.push({index1 + 1, index2, operations + 1}); //delete
            stateQueue.push({index1 + 1, index2 + 1, operations + 1}); //replace
        }
        return -1;
    }
};


template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
        os.width(3);
        os << element;
    }
    os << endl;
    return os;
}

class Solution2 {
public:
    int minDistance(string word1, string word2) {
        int word1Len = word1.size();
        int word2Len = word2.size();
        vector<vector<int>> minSteps(word1Len + 1, vector<int>(word2Len + 1, INT_MAX)); //word1[0,i)与word2[0,j)相等所需要的步数
        minSteps[0][0] = 0;
        for (int i = 0; i < word1Len; ++i) {
            for (int j = 0; j < word2Len; ++j) {
                minSteps[i][j + 1] = min(minSteps[i][j + 1], minSteps[i][j] + 1);//insert
                minSteps[i + 1][j] = min(minSteps[i + 1][j], minSteps[i][j] + 1);//delete
                minSteps[i + 1][j + 1] = min(
                    minSteps[i + 1][j + 1],
                    word1[i] == word2[j] ? minSteps[i][j] : minSteps[i][j] + 1
                );// replace or do nothing for w1[i]=w2[j]
            }
            //word2已满足，可以删除word1的字符
            minSteps[i + 1][word2Len] = min(minSteps[i + 1][word2Len], minSteps[i][word2Len] + 1);
        }
        for (int j = 0; j < word2Len; ++j)
            minSteps[word1Len][j + 1] = min(minSteps[word1Len][j + 1], minSteps[word1Len][j] + 1); //insert/append
        cout << minSteps;
        return minSteps[word1Len][word2Len];
    }
};

TEST_CASE("Edit Distance - BFS") {
    REQUIRE(Solution().minDistance("horse", "ros") == 3);
    REQUIRE(Solution().minDistance("intention", "execution") == 5);
//    REQUIRE(Solution().minDistance("pneumonoultramicroscopicsilicovolcanoconiosis", "ultramicroscopically") == 27);
}

TEST_CASE("Edit Distance") {
    REQUIRE(Solution2().minDistance("horse", "ros") == 3);
    REQUIRE(Solution2().minDistance("intention", "execution") == 5);
    REQUIRE(Solution2().minDistance("pneumonoultramicroscopicsilicovolcanoconiosis", "ultramicroscopically") == 27);
}
