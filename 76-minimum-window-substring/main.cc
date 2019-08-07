#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <queue>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
        os.width(3);
        os << element;
    }
    os << endl;
    return os;
}

class Solution {
public:
    string minWindow(string s, string t) {
        int sCount[256] = {0};
        int tCount[256] = {0};
        int notFound = 0;
        deque<int> index;
        int resultStart = -1, resultEnd = -1;
        for (char c:t) {
            if (tCount[c] == 0)
                ++notFound;
            ++tCount[c];
        }
        for (int i = 0; i < s.size(); ++i) {
            if (tCount[s[i]] == 0)
                continue;
            index.push_back(i);
            ++sCount[s[i]];
            if (sCount[s[i]] == tCount[s[i]])
                --notFound;
            while (sCount[s[index.front()]] > tCount[s[index.front()]]) {
                --sCount[s[index.front()]];
                index.pop_front();
            }
            if (notFound == 0) {
                if (resultStart == -1 || (index.back() - index.front()) < (resultEnd - resultStart)) {
                    resultStart = index.front();
                    resultEnd = index.back();
                }
            }
        }
        if (resultStart == -1)
            return "";
        return s.substr(resultStart, resultEnd - resultStart + 1);
    }
};

TEST_CASE("Minimum Window Substring") {
    REQUIRE(Solution().minWindow("ADOBECODEBANC", "ABC") == "BANC");
}
