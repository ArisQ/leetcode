#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
    int n;
public:
    int numDecodings(string s) {
        //1 2 3 ... 26
        n = s.size();
        if (n == 0)
            return 0;
        return numDecodings(s, 0);
    }

    int numDecodings(const string &s, int index) {
        if (index == n)
            return 1;
        if (s[index] == '0')
            return 0;
        if (index == n - 1)
            return 1;
        int result = numDecodings(s, index + 1);
        if (index + 1 < n && (s[index] == '1' || (s[index] == '2' && s[index + 1] <= '6')))
            result += numDecodings(s, index + 2);
        return result;
    }
};

class Solution2 {
    int n;
    vector<int> result;
public:
    int numDecodings(string s) {
        //1 2 3 ... 26
        n = s.size();
        if (n == 0)
            return 0;
        result = vector<int>(n, -1);
        return numDecodings(s, 0);
    }

    int numDecodings(const string &s, int index) {
        if (index == n)
            return 1;
        if (result[index] != -1)
            return result[index];
        if (s[index] == '0') {
            result[index] = 0;
            return 0;
        }
        if (index == n - 1) {
            return 1;
            result[index] = 1;
        }
        result[index] = numDecodings(s, index + 1);
        if (index + 1 < n && (s[index] == '1' || (s[index] == '2' && s[index + 1] <= '6')))
            result[index] += numDecodings(s, index + 2);
        return result[index];
    }
};

TEST_CASE("Decode Ways") {
    REQUIRE(Solution().numDecodings("12") == 2);
    REQUIRE(Solution().numDecodings("226") == 3);
    REQUIRE(Solution().numDecodings("") == 0);
    REQUIRE(Solution().numDecodings("0") == 0);
    REQUIRE(Solution().numDecodings("1") == 1);
    REQUIRE(Solution().numDecodings("9") == 1);
    REQUIRE(Solution().numDecodings("101") == 1); //10 1
    REQUIRE(Solution().numDecodings("1111") == 5); // 1 1 1 1; 11 1 1; 1 11 1; 1 1 11; 11 11
}

TEST_CASE("Decode Ways - Solution 2") {
    REQUIRE(Solution2().numDecodings("12") == 2);
    REQUIRE(Solution2().numDecodings("226") == 3);
    REQUIRE(Solution2().numDecodings("") == 0);
    REQUIRE(Solution2().numDecodings("0") == 0);
    REQUIRE(Solution2().numDecodings("1") == 1);
    REQUIRE(Solution2().numDecodings("9") == 1);
    REQUIRE(Solution2().numDecodings("101") == 1); //10 1
    REQUIRE(Solution2().numDecodings("1111") == 5); // 1 1 1 1; 11 1 1; 1 11 1; 1 1 11; 11 11
}
