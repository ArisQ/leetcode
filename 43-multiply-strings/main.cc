#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        string result = "0";
        if (num1 == "0")
            return result;
        vector<string> multiply_result_with_one_digit(10);//乘以0..9的结果
        int num2_max_index = num2.size() - 1;
        for (int i = num2_max_index; i >= 0; --i) {
            char d = num2[i] - '0';
            if (d == 0)
                continue;
            if (multiply_result_with_one_digit[d].empty()) {
                multiply_result_with_one_digit[d] = multiply_with_one_digit(num1, d);
            }
            accumulate(result, multiply_result_with_one_digit[d], num2_max_index - i);
        }
        return result;
    }

    void accumulate(string &num1, const string &num2, int shift = 0) {
        // num2!=0 否则有问题
        int i = num1.size() - 1 - shift;
        int j = num2.size() - 1;
        if (i < 0) { //num2直接插入到num1开头
            if (i < -1) //-1不插入0
                num1.insert(0, -i - 1, '0');
            num1.insert(0, num2);//如何num2==0，则会出错
            return;
        }

        int num2_begin = 0;
        if (i < j) {
            num1.insert(0, num2, 0, j - i);
            num2_begin = j - i;
            i = num1.size() - 1 - shift; //num1.size()发生变化
        }
        char carry = 0;
        for (; i >= 0 && !(j < num2_begin && carry == 0); --i, --j) {
            char r = num1[i] - '0';
            char s = 0;
            if (j >= num2_begin)
                s = num2[j] - '0';
            r += s + carry;
            carry = r / 10;
            r = r % 10;
            num1[i] = r + '0';
        }
        if (carry)
            num1.insert(num1.begin(), carry + '0');
    }

    string multiply_with_one_digit(string num, char digit) {
        char carry = 0;
        for (int i = num.size() - 1; i >= 0; --i) {
            char v = num[i] - '0';
            v = v * digit + carry;
            carry = v / 10;
            num[i] = v % 10 + '0';
        }
        if (carry)
            num.insert(num.begin(), carry + '0');
        return num;
    }
};

TEST_CASE("Multiply Strings") {
    REQUIRE(Solution().multiply("0", "0") == "0");
    REQUIRE(Solution().multiply("0", "1") == "0");
    REQUIRE(Solution().multiply("0", "2") == "0");
    REQUIRE(Solution().multiply("0", "9") == "0");
    REQUIRE(Solution().multiply("0", "10") == "0");
    REQUIRE(Solution().multiply("0", "0") == "0");
    REQUIRE(Solution().multiply("1", "0") == "0");
    REQUIRE(Solution().multiply("2", "0") == "0");
    REQUIRE(Solution().multiply("9", "0") == "0");
    REQUIRE(Solution().multiply("10", "0") == "0");
    REQUIRE(Solution().multiply("1", "1") == "1");
    REQUIRE(Solution().multiply("1", "2") == "2");
    REQUIRE(Solution().multiply("1", "9") == "9");
    REQUIRE(Solution().multiply("1", "10") == "10");
    REQUIRE(Solution().multiply("1", "1") == "1");
    REQUIRE(Solution().multiply("2", "1") == "2");
    REQUIRE(Solution().multiply("9", "1") == "9");
    REQUIRE(Solution().multiply("10", "1") == "10");
    REQUIRE(Solution().multiply("123", "456") == "56088");
}

TEST_CASE("Accumulate Strings - 123+456<<3") {
    string num1 = "123";
    string num2 = "456";
    Solution().accumulate(num1, num2, 3);
    REQUIRE(num1 == "456123");
}

TEST_CASE("Accumulate Strings - 123+456<<4") {
    string num1 = "123";
    string num2 = "456";
    Solution().accumulate(num1, num2, 4);
    REQUIRE(num1 == "4560123");
}

TEST_CASE("Accumulate Strings - 123+456<<1") {
    string num1 = "123";
    string num2 = "456";
    Solution().accumulate(num1, num2, 1);
    REQUIRE(num1 == "4683");
}

TEST_CASE("Accumulate Strings - 1107+738") {
    string num1 = "1107";
    string num2 = "738";
    Solution().accumulate(num1, num2);
    REQUIRE(num1 == "1845");
}

TEST_CASE("Accumulate Strings - 0+738") {
    string num1 = "0";
    string num2 = "738";
    Solution().accumulate(num1, num2);
    REQUIRE(num1 == "738");
}

// 未处理
//TEST_CASE("Accumulate Strings - 0+0") {
//    string num1 = "0";
//    string num2 = "0";
//    Solution().accumulate(num1, num2, 3);
//    REQUIRE(num1 == "0");
//}

TEST_CASE("Multiply Strings With One Digit") {
    REQUIRE(Solution().multiply_with_one_digit("123", '1' - '0') == "123");
    REQUIRE(Solution().multiply_with_one_digit("123", '2' - '0') == "246");
    REQUIRE(Solution().multiply_with_one_digit("123", '5' - '0') == "615");
    REQUIRE(Solution().multiply_with_one_digit("123", '9' - '0') == "1107");
}