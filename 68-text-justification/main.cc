#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string> &words, int maxWidth) {
        int count = 0;
        int wordSize;
        int start = 0;
        vector<string> result;
        for (int i = 0; i < words.size(); ++i) {
            wordSize = words[i].size();
            if (count + wordSize > maxWidth) {
                result.push_back(pack(words, start, i, count - 1, maxWidth));
                start = i;
                count = 0;
            } else {
                count += wordSize + 1;
            }
        }
    }

    string pack(const vector<string> &words, int start, int end, int sum, int maxWidth) {
        int extraBetween = (maxWidth - sum) / (end - start);
        int moreCount = maxWidth - sum - extraBetween * (end - start);
        string result(maxWidth,' ');
        for (int i = 0; i < end - start; ++i) {
            result += words[start + i];
            if (i < moreCount)
                result += ' ';
        }
        return result;
    }
};

TEST_CASE("Text Justification - Example 1") {
    vector<string> input{"This", "is", "an", "example", "of", "text", "justification."};
    vector<string> output{
        "This    is    an",
        "example  of text",
        "justification.  "
    };
    REQUIRE(Solution().fullJustify(input, 16) == output);
}

TEST_CASE("Text Justification - Example 2") {
    vector<string> input{"What", "must", "be", "acknowledgment", "shall", "be"};
    vector<string> output{

        "What   must   be",
        "acknowledgment  ",
        "shall be        "
    };
    REQUIRE(Solution().fullJustify(input, 16) == output);
}

TEST_CASE("Text Justification - Example 1") {
    vector<string> input{
        "Science", "is", "what", "we", "understand", "well", "enough", "to", "explain",
        "to", "a", "computer.", "Art", "is", "everything", "else", "we", "do"
    };
    vector<string> output{
        "Science  is  what we",
        "understand      well",
        "enough to explain to",
        "a  computer.  Art is",
        "everything  else  we",
        "do                  "
    };
    REQUIRE(Solution().fullJustify(input, 20) == output);
}
