#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int romanToInt(string s) {
//        Symbol       Value
//I             1
//V             5
//X             10
//L             50
//C             100
//D             500
//M             1000
        int result = 0;
        char p = 0;
        vector<int> rt(26);
        rt['I' - 'A'] = 1;
        rt['V' - 'A'] = 5;
        rt['X' - 'A'] = 10;
        rt['L' - 'A'] = 50;
        rt['C' - 'A'] = 100;
        rt['D' - 'A'] = 500;
        rt['M' - 'A'] = 1000;
        for (auto c:s) {
            if ((p == 'I' && (c == 'V' || c == 'X')) ||
                (p == 'X' && (c == 'L' || c == 'C')) ||
                (p == 'C' && (c == 'D' || c == 'M'))) {
                result += rt[c - 'A'] - rt[p - 'A'];
                p=0;
                continue;
            }
            result += rt[p - 'A'];
            p = 0;
            if (c == 'I' || c == 'X' || c == 'C') {
                p = c;
                continue;
            }
            result += rt[c - 'A'];
        }
        if (p != 0)
            result += rt[p - 'A'];
        return result;
    }
};

TEST_CASE("Roman to ingeter") {
    REQUIRE(Solution().romanToInt("III") == 3);
    REQUIRE(Solution().romanToInt("IV") == 4);
    REQUIRE(Solution().romanToInt("IX") == 9);
    REQUIRE(Solution().romanToInt("LVIII") == 58);
    REQUIRE(Solution().romanToInt("MCMXCIV") == 1994);
    REQUIRE(Solution().romanToInt("MDCCCLXXXIV") == 1884);
}
