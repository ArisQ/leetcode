#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <vector>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        vector<char> stack;
        auto close_bracket=[](char c) {
            if(c=='(') return ')';
            if(c=='[') return ']';
            if(c=='{') return '}';
            return static_cast<char>(0);
        };
        for(const auto &c:s) {
            if(c=='(' ||c=='[' ||c=='{' ) {
                stack.push_back(c);
            } else if(c==')' ||c==']' ||c=='}' ) {
                if(stack.empty() || close_bracket(stack.back())!=c)
                    return false;
                stack.pop_back();
            }
        }
        return stack.empty();
    }
};

TEST_CASE("Valid Parentheses") {
    REQUIRE(Solution().isValid("()") == true);
    REQUIRE(Solution().isValid("()[]{}") == true);
    REQUIRE(Solution().isValid("(]") == false);
    REQUIRE(Solution().isValid("([)]") == false);
    REQUIRE(Solution().isValid("{[]}") == true);
}
