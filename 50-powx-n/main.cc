#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
        cout.width(4);
        os << element;
    }
    os << endl;
    return os;
}

class Solution {
public:
    double myPow(double x, int n) {
        bool max_negative = false;
        if (n < 0) {
            if (n == -2147483647-1) {
                n = n + 1;
                max_negative = true;
            }
            n = -n;
            x = 1 / x;
        }
        vector<double> double_x_list;
        vector<int> pow_list;
        double double_x = x;
        double_x_list.push_back(x);
        pow_list.push_back(1);
        for (int i = 2; i < (1 << 30) && i <= n; i += i) {
            double_x = double_x * double_x;
            double_x_list.push_back(double_x);
            pow_list.push_back(i);
        }
        double result = 1;
        for (int i = pow_list.size() - 1; i >= 0; --i) {
            if (n >= pow_list[i]) {
                result *= double_x_list[i];
                n -= pow_list[i];
            }
        }
        if (max_negative)
            result = result * x;
        return result;
    }
};

TEST_CASE("Pow(x, n)") {
    REQUIRE((Solution().myPow(2.00000, 10) - 1024.00000) < 1e-6);
    REQUIRE((Solution().myPow(2.10000, 3) - 9.26100) < 1e-6);
    REQUIRE((Solution().myPow(2.00000, -2) - 0.25000) < 1e-6);
}

