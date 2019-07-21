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
    vector<int> findSubstring(string s, vector<string> &words) {
        vector<int> result;
        if (words.empty())
            return result;
        int word_size = words.size();
        int word_len = words[0].size();

        //合并重复单词，变成单词+单词次数的形式
        vector<string> unique_words;
        vector<int> word_times;
        for (auto &word:words) {
            bool new_word = true;
            for (int i = 0; i < unique_words.size(); ++i) {
                int k = 0;
                for (; k < word_len; ++k)
                    if (word[k] != unique_words[i][k])
                        break;
                if (k == word_len) {
                    new_word = false;
                    ++word_times[i];
                    break;
                }
            }
            if (new_word) {
                unique_words.push_back(word);
                word_times.push_back(1);
            }
        }

        //由于words长度相同，但是开头并不一定是长度的正数倍
        for (int i = 0; i < words[0].size(); ++i) {
            for (auto e:_findSubstring(s.substr(i), word_size, word_len, unique_words, word_times))
                result.push_back(e + i);
        }
        return result;
    }

    vector<int> _findSubstring(string s,
                               int words_size,
                               int word_len,
                               vector<string> &unique_words,
                               vector<int> &word_times) {
        vector<int> result;

        //将字符串按单词长度分组，每组变为单词索引的形式，不在给定的单词中则以unique_words.size()表示
        vector<int> word_index;
        word_index.reserve(s.size() / word_len);
        for (int i = 0; i < s.size(); i += word_len) {
            bool found = false;
            for (int j = 0; j < unique_words.size(); ++j) {
                int k = 0;
                for (; k < word_len; ++k)
                    if (s[i + k] != unique_words[j][k])
                        break;
                if (k == word_len) {
                    word_index.push_back(j);
                    found = true;
                    break;
                }
            }
            if (!found)
                word_index.push_back(unique_words.size()); //unique_words.size()表示不与unique_words中的单词匹配
        }

        if (word_index.size() < words_size)
            return result;

        //选定的word_size个单词中，对于index的单词出现的次数
        vector<int> unique_word_matched(unique_words.size() + 1, 0);
        word_times.push_back(0);

        int unmatched_word_count = 0;//单词数量未匹配的数量
        for (auto time:word_times) {
            if (time != 0)
                ++unmatched_word_count;
        }

        //初始化前word_size个单词匹配情况
        for (int i = 0; i < words_size; ++i) {
            if (unique_word_matched[word_index[i]] == word_times[word_index[i]])
                ++unmatched_word_count;
            ++unique_word_matched[word_index[i]];
            if (unique_word_matched[word_index[i]] == word_times[word_index[i]])
                --unmatched_word_count;
        }
        if (unmatched_word_count == 0)
            result.push_back(0); //正好匹配

        for (int i = 0; i < word_index.size() - words_size; ++i) {
            //去首，入尾部，向后移动选中的单词
            if (unique_word_matched[word_index[i]] == word_times[word_index[i]])
                ++unmatched_word_count; //移动前正好单词数匹配，移动后将不匹配，++
            --unique_word_matched[word_index[i]];
            if (unique_word_matched[word_index[i]] == word_times[word_index[i]])
                --unmatched_word_count;

            if (unique_word_matched[word_index[i + words_size]]
                == word_times[word_index[i + words_size]])
                ++unmatched_word_count;

            ++unique_word_matched[word_index[i + words_size]];
            if (unique_word_matched[word_index[i + words_size]]
                == word_times[word_index[i + words_size]])
                --unmatched_word_count;
            if (unmatched_word_count == 0)
                result.push_back((i + 1) * word_len);
        }
        return result;
    }
};

TEST_CASE("Substring with Concatenation of All Words - Example 1") {
    string s = "barfoothefoobarman";
    vector<string> words{"foo", "bar"};
    vector<int> output{0, 9};
    REQUIRE(Solution().findSubstring(s, words) == output);

}

TEST_CASE("Substring with Concatenation of All Words - Example 2") {
    string s = "wordgoodgoodgoodbestword";
    vector<string> words{"word", "good", "best", "word"};
    vector<int> output{};
    REQUIRE(Solution().findSubstring(s, words) == output);
}

TEST_CASE("Substring with Concatenation of All Words - Test 1") {
    string s = "wordgoodgoodgoodbestword";
    vector<string> words{"word", "good", "best", "good"};
    vector<int> output{8};
    REQUIRE(Solution().findSubstring(s, words) == output);
}
TEST_CASE("Substring with Concatenation of All Words - Test 2") {
    //"lingmindraboofooowingdingbarrwingmonkeypoundcake"
    //["fooo","barr","wing","ding","wing"]
    //13
    string s = "lingmindraboofooowingdingbarrwingmonkeypoundcake";
    vector<string> words{"fooo", "barr", "wing", "ding", "wing"};
    vector<int> output{13};
    REQUIRE(Solution().findSubstring(s, words) == output);
}
