#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    bool isNumber(string s) {
        int sLen = s.size();
        int i = 0;
        while (i < sLen && s[i] == ' ')
            ++i;
        if (i == sLen)
            return false;
        if (s[i] == '-' || s[i] == '+')
            ++i;
        bool dotFound = false;
        bool digitFound = false;
        for (; i < sLen; ++i) {
            int digit = s[i] - '0';
            if (s[i] == ' ') {
                for (; i < sLen; ++i)
                    if (s[i] != ' ')
                        return false;
                return digitFound;
            }
            if (digit >= 0 && digit <= 9) {
                digitFound = true;
                continue;
            }
            if (s[i] == '.') {
                if (dotFound)
                    return false;
                else
                    dotFound = true;
                continue;
            }
            if (s[i] == 'e') {
                break;
            }
            return false;
        }
        if (!digitFound)
            return false;
        if (i == sLen)
            return true;
        //s[i]==e;
        ++i;
        if (i != sLen && (s[i] == '-' || s[i] == '+'))
            ++i;
        digitFound = false;
        for (; i < sLen; ++i) {
            int digit = s[i] - '0';
            if (s[i] == ' ')
                break;
            if (digit < 0 || digit > 9)
                return false;
            else
                digitFound = true;
        }
        if (s[i] == ' ')
            for (; i < sLen; ++i)
                if (s[i] != ' ')
                    return false;
        return digitFound;
    }
};

TEST_CASE("Valid Number") {
    REQUIRE(Solution().isNumber("0") == true);
    REQUIRE(Solution().isNumber(" 0.1") == true);
    REQUIRE(Solution().isNumber("abc") == false);
    REQUIRE(Solution().isNumber("1 a") == false);
    REQUIRE(Solution().isNumber("2e10") == true);
    REQUIRE(Solution().isNumber("  -90e3   ") == true);
    REQUIRE(Solution().isNumber("1e") == false);
    REQUIRE(Solution().isNumber("e3") == false);
    REQUIRE(Solution().isNumber(" 6e-1") == true);
    REQUIRE(Solution().isNumber(" 99e2.5") == false);
    REQUIRE(Solution().isNumber("53.5e93") == true);
    REQUIRE(Solution().isNumber(" --6") == false);
    REQUIRE(Solution().isNumber("-+3") == false);
    REQUIRE(Solution().isNumber("95a54e53") == false);
    REQUIRE(Solution().isNumber("1 ") == true);
    REQUIRE(Solution().isNumber(". ") == false);
}

