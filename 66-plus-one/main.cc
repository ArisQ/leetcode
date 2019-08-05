#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {
        int carry = 1;
        int sum;
        for (int i = digits.size() - 1; i >= 0; --i) {
            sum = digits[i] + carry;
            digits[i] = sum % 10;
            carry = sum / 10;
            if (carry == 0)
                return digits;
        }
        //carry!=0
        digits.insert(digits.begin(), carry);
        return digits;
    }
};

TEST_CASE("Plus One - Example 1") {
    vector<int> input{1, 2, 3};
    vector<int> output{1, 2, 4};
    REQUIRE(Solution().plusOne(input) == output);
}

TEST_CASE("Plus One - Example 2") {
    vector<int> input{4, 3, 2, 1};
    vector<int> output{4, 3, 2, 2};
    REQUIRE(Solution().plusOne(input) == output);
}

TEST_CASE("Plus One - 0") {
    vector<int> input{0};
    vector<int> output{1};
    REQUIRE(Solution().plusOne(input) == output);
}

TEST_CASE("Plus One - 9") {
    vector<int> input{9};
    vector<int> output{1, 0};
    REQUIRE(Solution().plusOne(input) == output);
}
