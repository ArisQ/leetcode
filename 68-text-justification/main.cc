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
    vector<string> fullJustify(vector<string> &words, int maxWidth) {
        int count = 0;
        int wordSize;
        int start = 0;
        vector<string> result;
        for (int i = 0; i < words.size(); ++i) {
            wordSize = words[i].size();
            if (count + wordSize > maxWidth) {
                result.emplace_back(pack(words, start, i, count - 1, maxWidth));
                start = i;
                count = wordSize + 1; //wordSize should less than maxWidth
            } else {
                count += wordSize + 1;
            }
        }
        if (start != words.size()) {
            string line(maxWidth, ' ');
            int index = 0;
            for (int i = start; i < words.size(); ++i) {
                for (char c : words[i])
                    line[index++] = c;
                ++index;
            }
            result.push_back(line);
        }
        return result;
    }

    string pack(const vector<string> &words, int start, int end, int sum, int maxWidth) {
        string line(maxWidth, ' ');
        int index = 0;
        if (start + 1 == end) {//only one word
            for (char c : words[start])
                line[index++] = c;
            return line;
        }
        int extraBetween = (maxWidth - sum) / (end - start - 1); // end>start+1
        int moreCount = maxWidth - sum - extraBetween * (end - start - 1); //左侧多余空白的数量
        for (int i = start; i < end; ++i) {
            for (char c : words[i])
                line[index++] = c;
            ++index;//space between word
            index += extraBetween;//extra space
            if (i < start + moreCount)
                ++index;
        }
        return line;
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

TEST_CASE("Text Justification - Example 3") {
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
