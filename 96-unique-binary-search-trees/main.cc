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
    int numTrees(int n) {
        if (n == 0)
            return 0;
        vector<int> nums(n + 1, 0);
        nums[0] = 1;
        nums[1] = 1;
        for (int i = 2; i <= n; ++i) {
            for (int j = 0; j < i; ++j)
                nums[i] += nums[j] * nums[i - j - 1];
        }
        return nums[n];
    }
};

TEST_CASE("Unique Binary Search Trees") {
    REQUIRE(Solution().numTrees(3) == 5);
}
