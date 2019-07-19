#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    int removeElement(vector<int> &nums, int val) {
        auto i = nums.begin();
        for (auto j = i; j != nums.end(); ++j) {
            if (*j != val) {
                *i = *j;
                ++i;
            }
        }
        return static_cast<int>(i - nums.begin());
    }
};


ostream &operator<<(ostream &os, const vector<int> &array) {
    for (auto element:array) {
        os << element << " ";
    }
    return os;
}

bool vectorEqualInFirstKElement(const vector<int> &a, const vector<int> &b, int k) {
    if (a.size() < k || b.size() < k)
        return false;
    for (int i = 0; i < k; ++i)
        if (a[i] != b[i])
            return false;
    return true;
}

TEST_CASE("Remove Element - Example 1") {
    cout << "Remove Element - Example 1" << endl;
    vector<int> input{3, 2, 2, 3};
    vector<int> output{2, 2};
    cout << input << endl;
    cout << output << endl;
    int answer = Solution().removeElement(input, 3);
    REQUIRE(answer == output.size());
    REQUIRE(vectorEqualInFirstKElement(input, output, answer));
    cout << "answer num: " << answer << endl;
    cout << input << endl;
    cout << output << endl;
}

TEST_CASE("Remove Element - Example 2") {
    cout << "Remove Element - Example 2" << endl;
    vector<int> input{0, 1, 2, 2, 3, 0, 4, 2};
    vector<int> output{0, 1, 3, 0, 4};
    cout << input << endl;
    cout << output << endl;
    int answer = Solution().removeElement(input, 2);
    REQUIRE(answer == output.size());
    REQUIRE(vectorEqualInFirstKElement(input, output, answer));
    cout << "answer num: " << answer << endl;
    cout << input << endl;
    cout << output << endl;
}
