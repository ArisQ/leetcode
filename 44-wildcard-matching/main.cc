#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
        cout.width(3);
        os << element;
    }
    os << endl;
    return os;
}

class Solution {
public:
    bool isMatch(string s, string p) {
        int s_len = s.size();
        int p_len = p.size();
        vector<vector<int>> table(p_len + 1, vector<int>(s_len + 1, -1));
        table[0][0] = 1;
        for (int i = 1; i <= s_len; ++i)
            table[0][i] = 0;
        char match = 1;
        for (int i = 1; i <= p_len; ++i) {
            if (p[i - 1] != '*')
                match = 0;
            table[i][0] = match;
        }
        calcTable(s, p, table, p_len, s_len);
        return table[p_len][s_len] == 1;
    }

    void calcTable(const string &s, const string &p, vector<vector<int>> &table, int i, int j) {
        if (table[i][j] != -1)
            return;
        if (p[i - 1] == '*') {
            for (int k = j; k >= 0; --k) {
                if (table[i - 1][k] == -1)
                    calcTable(s, p, table, i - 1, k);
                if (table[i - 1][k] == 1) {
                    table[i][j] = 1;
                    return;
                }
            }
            table[i][j] = 0;
        } else if (p[i - 1] == '?' || p[i - 1] == s[j - 1]) {
            if (table[i - 1][j - 1] == -1)
                calcTable(s, p, table, i - 1, j - 1);
            table[i][j] = table[i - 1][j - 1];
        } else {
            table[i][j] = 0;
        }
    }
};

TEST_CASE("Wildcard Matching") {
    REQUIRE(!Solution().isMatch("aa", "a"));
    REQUIRE(Solution().isMatch("aa", "*"));
    REQUIRE(!Solution().isMatch("cb", "?a"));
    REQUIRE(Solution().isMatch("adceb", "*a*b"));
    REQUIRE(!Solution().isMatch("acdcb", "a*c?b"));
    REQUIRE(Solution().isMatch("ab", "?*"));
    REQUIRE(!Solution().isMatch("aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba", "a*******b"));
    REQUIRE(!Solution().isMatch(
        "abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb",
        "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb"
    ));
}
