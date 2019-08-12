#define CATCH_CONFIG_MAIN

#include <catch.hpp>

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

ostream &operator<<(ostream &os, const vector<string> &array) {
    for (auto element:array) {
        os << element << endl;
    }
    os << endl;
    return os;
}

class Solution {
public:
    bool isScramble(string s1, string s2) {
//        if(s1.size()!=s2.size())
//            return false;
        return isScramble(s1, s2, 0, 0, s1.size());
    }

    bool isScramble(const string &s1, const string &s2,
                    int s1Start, int s2Start, int len //s1 start
    ) {
        cout << "is Scramble " << s1Start << " " << s2Start << " " << len << endl;
        if (len == 1 && s1[s1Start] == s2[s2Start]) {
            cout << "single true" << endl;
            return true;
        }
        int s1Count[256];
        int s2Count[256];
        memset(s1Count, 0, sizeof(s1Count));
        memset(s2Count, 0, sizeof(s2Count));
        int unmatchCount = 0;
        char c1, c2;
        for (int i = 0; i < len - 1; ++i) {
            c1 = s1[s1Start + i];
            c2 = s2[s2Start + i];
            ++s1Count[c1];
            ++s2Count[c2];
            //计算unmatchCount，c1==c2则不变，不需要计算
            if (c1 != c2) {
                if (s1Count[c1] == s2Count[c1]) {
                    --unmatchCount;
                } else if (s1Count[c1] == s2Count[c1] + 1) {
                    ++unmatchCount;
                }
                if (s1Count[c2] == s2Count[c2]) {
                    --unmatchCount;
                } else if (s2Count[c2] == s1Count[c2] + 1) {
                    ++unmatchCount;
                }
            }
            if (unmatchCount == 0) {
                cout << "matched at " << i << endl;
                if (isScramble(s1, s2, s1Start, s2Start, i + 1) &&
                    isScramble(s1, s2, s1Start + i + 1, s2Start + i + 1, len - i - 1)) {
                    cout << "true" << endl;
                    return true;
                }
            }
        }
        //reverse
        memset(s1Count, 0, sizeof(s1Count));
        memset(s2Count, 0, sizeof(s2Count));
        unmatchCount = 0;
        for (int i = 0; i < len - 1; ++i) {
            c1 = s1[s1Start + i];
            c2 = s2[s2Start + len - 1 - i];
            ++s1Count[c1];
            ++s2Count[c2];
            //计算unmatchCount，c1==c2则不变，不需要计算
            if (c1 != c2) {
                if (s1Count[c1] == s2Count[c1]) {
                    --unmatchCount;
                } else if (s1Count[c1] == s2Count[c1] + 1) {
                    ++unmatchCount;
                }
                if (s1Count[c2] == s2Count[c2]) {
                    --unmatchCount;
                } else if (s2Count[c2] == s1Count[c2] + 1) {
                    ++unmatchCount;
                }
            }
            if (unmatchCount == 0) {
                cout << "reverse matched at " << i << endl;
                if (isScramble(s1, s2, s1Start, s2Start + len - 1 - i, i + 1) &&
                    isScramble(s1, s2, s1Start + i + 1, s2Start, len - i - 1)) {
                    cout << "true" << endl;
                    return true;
                }
            }
        }
        cout << "false" << endl;
        return false;
    }

    vector<string> scramble(string s) {
        cout << "string " << s << endl;
        size_t len = s.size();
        if (len == 0)
            return vector<string>();
        if (len == 1)
            return vector<string>{s};
        //len>=2
        vector<string> result, part1, part2;
        for (size_t i = 1; i < len; ++i) {
            part1 = scramble(s.substr(0, i));
            part2 = scramble(s.substr(i, len - i));
//            cout << "part1 " << part1 << " Part2 " << part2 << endl;
            for (auto &p1:part1)
                for (auto &p2:part2)
                    result.push_back(p1 + p2);
            for (auto &p1:part1)
                for (auto &p2:part2)
                    result.push_back(p2 + p1);
        }
        return result;
    }

    void trans(const string &s, vector<bool> &used, int index, string selected, vector<string> &result) {
        size_t len = s.size();
        if (index == s.size())
            result.push_back(selected);
        for (size_t i = 0; i < len; ++i) {
            if (used[i] == false) {
                used[i] = true;
                selected.push_back(s[i]);
                trans(s, used, index + 1, selected, result);
                selected.pop_back();
                used[i] = false;
            }
        }
    }
};


TEST_CASE("Scramble String") {
    REQUIRE(Solution().isScramble("great", "rgeat") == true);
    REQUIRE(Solution().isScramble("abcde", "caebd") == false);
    /*
     auto scrambleResult = Solution().scramble("great");
 //    cout << scrambleResult << endl;

     string s = "great";
     string selected;
     vector<string> transResult;
     vector<bool> used(s.size(), false);
     Solution().trans(s, used, 0, selected, transResult);
     cout << "================================" << endl;
     cout << transResult << endl;
     for (auto &r:transResult) {
         bool isScramble = false;
         for (auto &sr:scrambleResult) {
             if (sr == r) {
                 isScramble = true;
                 break;
             }
         }
         cout << r << " " << (isScramble ? "true" : "false") << endl;
     }
     cout << scrambleResult.size() << " " << transResult.size() << endl;
 */
}

