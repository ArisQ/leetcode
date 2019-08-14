#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
        os.width(3);
        os << element;
    }
    os << endl;
    return os;
}

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int s1Len = s1.size(), s2Len = s2.size(), s3Len = s3.size();
        if (s1Len + s2Len != s3Len)
            return false;
        vector<vector<int>> match(s1Len + 1, vector<int>(s2Len + 1, -1));
        match[0][0] = 1;
        return isInterleave(s1, s2, s3, match, s1Len, s2Len) == 1;
    }

    int isInterleave(const string &s1, const string &s2, const string &s3,
                     vector<vector<int>> &match, int i, int j) {
        if (match[i][j] != -1)
            return match[i][j];
        int k = i + j - 1;
        match[i][j] = 0;
        if ((i > 0 && s1[i - 1] == s3[k] && isInterleave(s1, s2, s3, match, i - 1, j) == 1) ||
            (j > 0 && s2[j - 1] == s3[k] && isInterleave(s1, s2, s3, match, i, j - 1) == 1)) {
            match[i][j] = 1;
        }
        return match[i][j];
    }
};

TEST_CASE("Interleaving String") {
    REQUIRE(Solution().isInterleave("aabcc", "dbbca", "aadbbcbcac") == true);
    REQUIRE(Solution().isInterleave("aabcc", "dbbca", "aadbbbaccc") == false);
    REQUIRE(Solution().isInterleave(
        "cabbacccabacbcaabaccacacc",
        "bccacbacabbabaaacbbbbcbbcacc",
        "cbccacabbacabbbaacbcacaaacbbacbcaabbbbacbcbcacccacacc"
    ) == true);
}
