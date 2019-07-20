#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    int divide(int dividend, int divisor) {
        int sign = 1;
        int result = 0;
        int multiplier;
        int multi_divisor;
        if (dividend == -2147483648 && divisor == -1) {
            return 2147483647; //溢出
        }
        if (dividend == -2147483648 && divisor == 1) {
            return -2147483648; //因为结果以绝对值计算，-2147483648会溢出，因此单独处理
        }
        if (dividend > 0) {
            sign = -sign;
            dividend = -dividend;
        }
        if (divisor > 0) {
            sign = -sign;
            divisor = -divisor;
        }
        // 保证dividend<=0 && divisor<0；因此结果会为正数，最后按sign决定是否取反
        while (dividend <= divisor) {
            multi_divisor = divisor;
            multiplier = 1;
            while (multi_divisor >= -(1 << 30) && dividend <= multi_divisor + multi_divisor) {
                multiplier += multiplier; //不会超出2147483647
                multi_divisor += multi_divisor;
            }
            // -(1 << 31) <= multi_divisor+multi_divisor <[=] dividend <= multi_divisor < 0
            dividend -= multi_divisor;
            result += multiplier;
        }
        if (sign < 0)
            result = -result;
        return result;
    }
};

TEST_CASE("Divide Two Integers") {
    REQUIRE(Solution().divide(10, 3) == 3);
    REQUIRE(Solution().divide(7, -3) == -2);
    REQUIRE(Solution().divide(-2147483648, -1) == 2147483647);//溢出
    REQUIRE(Solution().divide(-2147483648, 1) == -2147483648);
}

