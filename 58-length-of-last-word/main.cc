#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int space_index = -1;
        int word_len = 0;
        for (int i = 0; i < s.size(); ++i)
            if (s[i] == ' ')
                space_index = i;
            else
                word_len = i - space_index;
        return word_len;
    }
};

TEST_CASE("Length of Last Word") {
    REQUIRE(Solution().lengthOfLastWord("Hello world") == 5);
    REQUIRE(Solution().lengthOfLastWord("a ") == 1);
}
