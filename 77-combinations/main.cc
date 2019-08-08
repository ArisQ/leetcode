#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <set>

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
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> selected;
        selected.reserve(n);
        combine(result, selected, n, k, 0);
        cout << result;
        return result;
    }

    void combine(vector<vector<int>> &result, vector<int> &selected, int n, int k, int start) {
        for (int i = start; i <= n - k; ++i) {
            selected.push_back(i + 1);
            if (k == 1)
                result.push_back(selected);
            else
                combine(result, selected, n, k - 1, i + 1);
            selected.pop_back();
        }
    }
};

TEST_CASE("Combinations") {
    vector<vector<int>> output = {
        {2, 4},
        {3, 4},
        {2, 3},
        {1, 2},
        {1, 3},
        {1, 4},
    };
    auto answer = Solution().combine(4, 2);
    REQUIRE(multiset<vector<int>>(answer.begin(), answer.end()) == multiset<vector<int>>(output.begin(), output.end()));
}

TEST_CASE("Combinations - Time Limit Exceeded") {
    auto answer = Solution().combine(20, 16);
    //原因：递归combine，返回了result，造成复制；改为void即可
}

