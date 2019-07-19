#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <string>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        int haystack_size = static_cast<int>( haystack.size());
        int needle_size = static_cast<int>(needle.size());
        for (int i = 0; i <= haystack_size - needle_size; ++i) {
            int j;
            for (j = 0; j < needle_size; ++j) {
                if (haystack[i + j] != needle[j])
                    break;
            }
            if (j == needle_size)
                return i;
        }
        return -1;
    }
};

TEST_CASE("Implement strStr() - Example 1") {
    cout << "Implement strStr() - Example 1" << endl;
    string haystack = "hello";
    string needle = "ll";
    int output = 2;
    cout << haystack << endl;
    cout << needle << endl;
    cout << output << endl;
    int answer = Solution().strStr(haystack, needle);
    REQUIRE(answer == output);
}


TEST_CASE("Implement strStr() - Example 2") {
    cout << "Implement strStr() - Example 2" << endl;
    string haystack = "aaaaa";
    string needle = "bba";
    int output = -1;
    cout << haystack << endl;
    cout << needle << endl;
    cout << output << endl;
    int answer = Solution().strStr(haystack, needle);
    REQUIRE(answer == output);
}

TEST_CASE("Implement strStr() - Example 3") {
    cout << "Implement strStr() - Example 3" << endl;
    string haystack = "aaaaa";
    string needle = "";
    int output = 0;
    cout << haystack << endl;
    cout << needle << endl;
    cout << output << endl;
    int answer = Solution().strStr(haystack, needle);
    REQUIRE(answer == output);
}
