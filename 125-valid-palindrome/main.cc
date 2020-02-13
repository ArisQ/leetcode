#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    inline bool isAlphanumeric(char c) {
        return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9');
    }
    inline char normalize(char c) {
        if ('A' <= c && c <= 'Z')
            return c - 'A' + 'a';
        return c;
    }
    bool isPalindrome(string s) {
        int n = s.size();
        int i = 0, j = n - 1;
        while (i < j) {
            if (!isAlphanumeric(s[i])) {
                // cout << i << " " << s[i] << " is not alphanumeric." << endl;
                ++i;
            } else if (!isAlphanumeric(s[j])) {
                // cout << j << " " << s[j] << " is not alphanumeric." << endl;
                --j;
            } else if (normalize(s[i]) == normalize(s[j])) {
                // cout << i << " " << j << " " << s[i] << "=" << s[j] << endl;
                ++i;
                --j;
            } else {
                // cout << i << " " << j << " " << s[i] << "!=" << s[j] << endl;
                return false;
            }
        }
        return true;
    }
};

TEST_CASE("Valid Palindrome") {
    REQUIRE(Solution().isPalindrome("A man, a plan, a canal: Panama"));
    REQUIRE(!Solution().isPalindrome("race a car"));
}
