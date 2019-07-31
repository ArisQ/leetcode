#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
        cout.width(3);
        os << element;
    }
    os << endl;
    return os;
}

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs) {
        vector<vector<string>> result;
        vector<vector<int>> char_count;
        for (auto &str:strs) {
            vector<int> count;
            charCount(str, count);
            int i = 0;
            for (; i < result.size(); ++i) {
                if (charCountEqual(count, char_count[i])) {
                    result[i].push_back(str);
                    break;
                }
            }
            if (i != result.size())
                continue;
            result.emplace_back(vector<string>{str});
            char_count.push_back(count);
        }
        return result;
    }

    void charCount(string &str, vector<int> &count) {
        count.resize(27);
        count[26] = 0;
        for (char c : str) {
            ++count[c - 'a'];
            ++count[26];
        }
    }

    bool charCountEqual(vector<int> &p, vector<int> &q) {
        if (p[26] != q[26])
            return false;
        for (int i = 0; i < 26; ++i)
            if (p[i] != q[i])
                return false;
        return true;
    }
};

template<typename T>
multiset<multiset<T>> vectorToMultiset(const vector<vector<T>> &v) {
    multiset<multiset<T>> result;
    for (auto &e:v)
        result.emplace(multiset<T>{e.begin(), e.end()});
    return result;
}

TEST_CASE("Group Anagrams") {
    vector<string> input{"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> output{
        {"ate", "eat", "tea"},
        {"nat", "tan"},
        {"bat"}
    };
    REQUIRE(vectorToMultiset(Solution().groupAnagrams(input)) == vectorToMultiset(output));
}

