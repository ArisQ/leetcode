#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;


ostream &operator<<(ostream &os, const vector<pair<int, int>> &array) {
    for (auto element:array) {
        os << element.first << " " << element.second << endl;
    }
    os << endl;
    return os;
}

class Solution {
    vector<pair<int, int>> index;
public:
    int numDistinct(string s, string t) {
        if (t.size() == 0)
            return 1;
        if (s.size() == 0)
            return 0;
        auto result = numDistinct(s, t, 0, 0);
        sort(index.begin(), index.end());
//        cout << index;
        return result;
    }

    //si<s.size()  ti<t.size()
    int numDistinct(const string &s, const string &t, int si, int ti) {
        cout << si << " " << ti << endl;
        index.emplace_back(make_pair(si, ti));
        if (s[si] == t[ti]) {
            if (ti + 1 == t.size()) {
                cout << "match " << si << " " << ti << endl;
                if (si + 1 == s.size())
                    return 1;
                return 1 + numDistinct(s, t, si + 1, ti);
            } else if (si + 1 == s.size())
                return 0;
            else
                return numDistinct(s, t, si + 1, ti + 1) + numDistinct(s, t, si + 1, ti);
        } else {
            if (si + 1 == s.size())
                return 0;
            return numDistinct(s, t, si + 1, ti);
        }
    }
};

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &array) {
    for (auto element:array) {
//        os.width(3);
        os << element << " ";
    }
    os << endl;
    return os;
}

class Solution2 {
public:
    int numDistinct(string s, string t) {
        if (t.size() == 0)
            return 1;
        if (s.size() == 0)
            return 0;
        vector<vector<long>> num(s.size(), vector<long>(t.size()));
        long match = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == t[0])
                ++match;
            num[i][0] = match;
        }
        for (int i = 1; i < t.size(); ++i) {
            num[0][i] = 0;
        }
        for (int i = 1; i < t.size(); ++i) {
            for (int j = 1; j < s.size(); ++j) {
                if (s[j] == t[i]) {
                    num[j][i] = num[j - 1][i - 1] + num[j - 1][i];
                } else {
                    num[j][i] = num[j - 1][i];
                }
            }
        }
        cout << num;
        return num[s.size() - 1][t.size() - 1];
    }
};

TEST_CASE("Distinct Subsequences") {
    REQUIRE(Solution().numDistinct("rabbbit", "rabbit") == 3);
    REQUIRE(Solution().numDistinct("babgbag", "bag") == 5);
//    REQUIRE(Solution().numDistinct(
//        "xslledayhxhadmctrliaxqpokyezcfhzaskeykchkmhpyjipxtsuljkwkovmvelvwxzwieeuqnjozrfwmzsylcwvsthnxujvrkszqwtglewkycikdaiocglwzukwovsghkhyidevhbgffoqkpabthmqihcfxxzdejletqjoxmwftlxfcxgxgvpperwbqvhxgsbbkmphyomtbjzdjhcrcsggleiczpbfjcgtpycpmrjnckslrwduqlccqmgrdhxolfjafmsrfdghnatexyanldrdpxvvgujsztuffoymrfteholgonuaqndinadtumnuhkboyzaqguwqijwxxszngextfcozpetyownmyneehdwqmtpjloztswmzzdzqhuoxrblppqvyvsqhnhryvqsqogpnlqfulurexdtovqpqkfxxnqykgscxaskmksivoazlducanrqxynxlgvwonalpsyddqmaemcrrwvrjmjjnygyebwtqxehrclwsxzylbqexnxjcgspeynlbmetlkacnnbhmaizbadynajpibepbuacggxrqavfnwpcwxbzxfymhjcslghmajrirqzjqxpgtgisfjreqrqabssobbadmtmdknmakdigjqyqcruujlwmfoagrckdwyiglviyyrekjealvvigiesnvuumxgsveadrxlpwetioxibtdjblowblqvzpbrmhupyrdophjxvhgzclidzybajuxllacyhyphssvhcffxonysahvzhzbttyeeyiefhunbokiqrpqfcoxdxvefugapeevdoakxwzykmhbdytjbhigffkmbqmqxsoaiomgmmgwapzdosorcxxhejvgajyzdmzlcntqbapbpofdjtulstuzdrffafedufqwsknumcxbschdybosxkrabyfdejgyozwillcxpcaiehlelczioskqtptzaczobvyojdlyflilvwqgyrqmjaeepydrcchfyftjighntqzoo",
//        "rwmimatmhydhbujebqehjprrwfkoebcxxqfktayaaeheys") == 543744000);
}

TEST_CASE("Distinct Subsequences - Solution 2") {
    REQUIRE(Solution2().numDistinct("rabbbit", "rabbit") == 3);
    REQUIRE(Solution2().numDistinct("babgbag", "bag") == 5);
    REQUIRE(Solution2().numDistinct(
        "xslledayhxhadmctrliaxqpokyezcfhzaskeykchkmhpyjipxtsuljkwkovmvelvwxzwieeuqnjozrfwmzsylcwvsthnxujvrkszqwtglewkycikdaiocglwzukwovsghkhyidevhbgffoqkpabthmqihcfxxzdejletqjoxmwftlxfcxgxgvpperwbqvhxgsbbkmphyomtbjzdjhcrcsggleiczpbfjcgtpycpmrjnckslrwduqlccqmgrdhxolfjafmsrfdghnatexyanldrdpxvvgujsztuffoymrfteholgonuaqndinadtumnuhkboyzaqguwqijwxxszngextfcozpetyownmyneehdwqmtpjloztswmzzdzqhuoxrblppqvyvsqhnhryvqsqogpnlqfulurexdtovqpqkfxxnqykgscxaskmksivoazlducanrqxynxlgvwonalpsyddqmaemcrrwvrjmjjnygyebwtqxehrclwsxzylbqexnxjcgspeynlbmetlkacnnbhmaizbadynajpibepbuacggxrqavfnwpcwxbzxfymhjcslghmajrirqzjqxpgtgisfjreqrqabssobbadmtmdknmakdigjqyqcruujlwmfoagrckdwyiglviyyrekjealvvigiesnvuumxgsveadrxlpwetioxibtdjblowblqvzpbrmhupyrdophjxvhgzclidzybajuxllacyhyphssvhcffxonysahvzhzbttyeeyiefhunbokiqrpqfcoxdxvefugapeevdoakxwzykmhbdytjbhigffkmbqmqxsoaiomgmmgwapzdosorcxxhejvgajyzdmzlcntqbapbpofdjtulstuzdrffafedufqwsknumcxbschdybosxkrabyfdejgyozwillcxpcaiehlelczioskqtptzaczobvyojdlyflilvwqgyrqmjaeepydrcchfyftjighntqzoo",
        "rwmimatmhydhbujebqehjprrwfkoebcxxqfktayaaeheys") == 543744000);
}

