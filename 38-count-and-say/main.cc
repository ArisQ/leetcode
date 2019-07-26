#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    string int_to_decimal_string(int x) {
        // can use to_string() instead
        string result;
        if (x >= 10) {
            result = int_to_decimal_string(x / 10);
            x = x % 10;
        }
        result.push_back('0' + char(x));
        return result;
    }

    string countAndSay(int n) {
        // 1 ≤ n ≤ 30
        string x = "1", y;
        string *p = &x, *q = &y, *temp = nullptr;
        for (; n > 1; --n) {
            char c = (*p)[0];
            int count = 1;
            for (int i = 1; i < p->size(); ++i) {
                if ((*p)[i] == c) {
                    ++count;
                } else { // p[i]!=c
                    *q += int_to_decimal_string(count);
                    q->push_back(c);
                    c = (*p)[i];
                    count = 1;
                }
            }
            *q += int_to_decimal_string(count);
            q->push_back(c);
            temp = p;
            p = q;
            q = temp;
            *q = "";
        }
        //n==1
        return *p;
    }
};

TEST_CASE("Count and Say") {
    REQUIRE(Solution().countAndSay(1) == "1");
    REQUIRE(Solution().countAndSay(2) == "11");
    REQUIRE(Solution().countAndSay(3) == "21");
    REQUIRE(Solution().countAndSay(4) == "1211");
    REQUIRE(Solution().countAndSay(5) == "111221");
    REQUIRE(Solution().countAndSay(6) == "312211");
    // cout << Solution().countAndSay(30) << endl;
    // cout << Solution().countAndSay(31) << endl;
}


TEST_CASE("int_to_decimal_string") {
    REQUIRE(Solution().int_to_decimal_string(1) == "1");
    REQUIRE(Solution().int_to_decimal_string(5) == "5");
    REQUIRE(Solution().int_to_decimal_string(10) == "10");
    REQUIRE(Solution().int_to_decimal_string(15) == "15");
    REQUIRE(Solution().int_to_decimal_string(20) == "20");
    REQUIRE(Solution().int_to_decimal_string(100) == "100");
}
