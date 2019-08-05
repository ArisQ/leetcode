#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        if (b.size() > a.size())
            return addSortedBinary(b, a);
        return addSortedBinary(a, b);
    }

    string addSortedBinary(string &a, string &b) {
        int carry = 0;
        int aLen_1 = a.size() - 1;
        int bLen_1 = b.size() - 1;
        int x, y, sum;
        for (int i = 0; i <= aLen_1; ++i) {
            x = a[aLen_1 - i] - '0';
            if (i <= bLen_1)
                y = b[bLen_1 - i] - '0';
            else if (carry != 0)
                y = 0;
            else
                break;
            sum = x + y + carry;//0,1,2,3
            a[aLen_1 - i] = ((sum == 1 || sum == 3) ? '1' : '0');
            carry = (sum >= 2 ? 1 : 0);
        }
        if (carry)
            a.insert(a.begin(), '1');
        return a;
    }
};

TEST_CASE("Add Binary") {
    REQUIRE(Solution().addBinary("11", "1") == "100");
    REQUIRE(Solution().addBinary("1010", "1011") == "10101");
}
