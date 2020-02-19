#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
    vector<vector<string>> result;
    vector<string> part;
    int n = 0;
public:
    vector<vector<string>> partition(string s) {
        n = s.size();
        helper(s, 0);
        return result;
    }

    void helper(const string &s, int i) {
        if (i >= n) {
            if (!part.empty())
                result.push_back(part);
            return;
        }
        for (int j = i; j < n; ++j) {
            int p = i, q = j;
            while (p < q) { // TODO: 优化判断是否为palindrome的方法
                if (s[p] != s[q])
                    break;
                ++p;
                --q;
            }
            if (p < q)
                continue;
            // palindrome
            part.push_back(s.substr(i, j - i + 1));
            helper(s, j + 1);
            part.pop_back();
        }
    }
};

TEST_CASE("Palindrome Partitioning") {
    vector<vector<string>> output{{"aa", "b"}, {"a", "a", "b"}};
    auto answer = Solution().partition("aab");
    REQUIRE(set<vector<string>>(output.cbegin(), output.cend()) == set<vector<string>>(answer.cbegin(), answer.cend()));
}
