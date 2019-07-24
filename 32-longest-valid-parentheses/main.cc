#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
        os << element << " ";
    }
    os << endl;
    return os;
}

class Solution {
public:
    int longestValidParentheses(string s) {
        int max_count = 0; //最大长度
        int valid_count = 0; //目前最有效长度
        int left_count = 0; //最有效长度中剩余的左括号(数量

        for (auto c:s) {
            if (c == '(') {
                ++left_count;
                ++valid_count;
            } else {
                if (left_count > 0) {
                    --left_count;
                    ++valid_count;
                } else {  //left_count==0
                    if (valid_count > max_count)
                        max_count = valid_count;
                    left_count = 0;
                    valid_count = 0;
                }
            }
        }
        if (left_count == 0) {
            //最后一段完全匹配，即目前最有效长度中( )数量相等，为有效匹配
            if (valid_count > max_count)
                max_count = valid_count;
        } else {
            //不是有效匹配，有多余的（，需要确认最后一段匹配中的最大长度有效匹配
            //从右向左匹配
            //因为最后一段left_count>0, 即(比)多，因此从后向前匹配，最坏left剩余的）肯定为0
            //否则剩余的）会将最后一段匹配分隔成两段，与最后一段有效匹配矛盾（不是一段）
            int s_len = s.size();
            int remain_count = valid_count;
            valid_count = 0;
            left_count = 0;
            for (int i = 1; i <= remain_count; ++i) { // s[-remain:]子字符串以(开头，且(>)
                char c = s[s_len - i];
                if (c == ')') {
                    ++left_count;
                    ++valid_count;
                } else {
                    if (left_count > 0) {
                        --left_count;
                        ++valid_count;
                    } else {  //left_count==0
                        if (valid_count > max_count)
                            max_count = valid_count;
                        left_count = 0;
                        valid_count = 0;
                    }
                }
            }
            if (valid_count > max_count) //left_cout必为0
                max_count = valid_count;
        }
        return max_count;
    }
};

TEST_CASE("Longest Valid Parentheses") {
    REQUIRE(Solution().longestValidParentheses("(()") == 2);
    REQUIRE(Solution().longestValidParentheses(")()())") == 4);
    REQUIRE(Solution().longestValidParentheses("()(()") == 2);
    REQUIRE(Solution().longestValidParentheses("(()(((()") == 2);

    REQUIRE(Solution().longestValidParentheses("(())(") == 4);
}


class SolutionStackVersion {
public:
    int longestValidParentheses(string s) {
        int max_count = 0;
        stack<int> stk;
        stk.push(-1);//如果与-1匹配，则说明该位置的)没有匹配的(（此时stk为空）,则以该)位置作为标志替换-1
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(')
                stk.push(i);
            else {
                stk.pop(); //对于每个)找到与之配对的)；如果无效/找不到，则结束之前的匹配，重新开始
                if (stk.empty())
                    stk.push(i);
                else if (i - stk.top() > max_count)
                    max_count = i - stk.top();
            }
        }

        return max_count;
    }
};

TEST_CASE("Longest Valid Parentheses - Stack Version") {
    REQUIRE(SolutionStackVersion().longestValidParentheses("(()") == 2);
    REQUIRE(SolutionStackVersion().longestValidParentheses(")()())") == 4);
    REQUIRE(SolutionStackVersion().longestValidParentheses("()(()") == 2);
    REQUIRE(SolutionStackVersion().longestValidParentheses("(()(((()") == 2);

    REQUIRE(SolutionStackVersion().longestValidParentheses("(())(") == 4);
}
