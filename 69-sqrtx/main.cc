#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    int mySqrt(int x) {
        if (x <= 1)
            return x;
        int a = 1, b = min(x, 46341), m, squareM; //x is int which less than INT_MAX(=2147483647)，sqrt(2147483647)=46340
        while (a + 1 < b) {
            m = (a + b) / 2;
            squareM = m * m;
            if (squareM == x)
                return m;
            else if (squareM < x)
                a = m;
            else // squareM>x
                b = m;
        }
        return a;
    }
};

TEST_CASE("Sqrt(x)") {
    REQUIRE(Solution().mySqrt(1) == 1);
    REQUIRE(Solution().mySqrt(2) == 1);
    REQUIRE(Solution().mySqrt(3) == 1);
    REQUIRE(Solution().mySqrt(4) == 2);
    REQUIRE(Solution().mySqrt(5) == 2);
    REQUIRE(Solution().mySqrt(6) == 2);
    REQUIRE(Solution().mySqrt(7) == 2);
    REQUIRE(Solution().mySqrt(8) == 2);
    REQUIRE(Solution().mySqrt(9) == 3);
    REQUIRE(Solution().mySqrt(10) == 3);
    REQUIRE(Solution().mySqrt(2147395599) == 46339);
    for (int i = 1; i < 100; ++i)
        for (int j = 0; j <= 2 * i; ++j)
            REQUIRE(Solution().mySqrt(i * i + j) == i); // i^2 < x < (i+1)^2-1=i^2+2*i
}
