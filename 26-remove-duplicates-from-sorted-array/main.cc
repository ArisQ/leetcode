#define CATCH_CONFIG_MAIN

#include <catch.hpp>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int> &nums) {
        auto i = nums.begin();
        if (i == nums.end())
            return 0;
        for (auto j = i + 1; j != nums.end(); ++j) {
            if (*i != *j) {
                ++i;
                *i = *j;
            }
        }
        return static_cast<int>(i - nums.begin() + 1);
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

TEST_CASE("Remove Duplicates from Sorted Array - Example 1") {
    vector<int> input{1, 1, 2};
    vector<int> output{1, 2};
    cout << input << endl;
    cout << output << endl;
    int answer = Solution().removeDuplicates(input);
    REQUIRE(answer == output.size());
    REQUIRE(vectorEqualInFirstKElement(input, output, answer));
    cout << "answer num: " << answer << endl;
    cout << input << endl;
    cout << output << endl;
}


TEST_CASE("Remove Duplicates from Sorted Array - Example 2") {
    vector<int> input{0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    vector<int> output{0, 1, 2, 3, 4};
    cout << input << endl;
    cout << output << endl;
    int answer = Solution().removeDuplicates(input);
    REQUIRE(answer == output.size());
    REQUIRE(vectorEqualInFirstKElement(input, output, answer));
    cout << "answer num: " << answer << endl;
    cout << input << endl;
    cout << output << endl;
}
