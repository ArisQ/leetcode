#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <bitset>

using namespace std;

ostream &operator<<(ostream &os, const vector<int> &array) {
    for (auto element:array) {
        os.width(4);
        os << bitset<3>(element);
    }
    os << endl;
    return os;
}

class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> result;
        result.reserve(1 << n);
        result.push_back(0);
        int len = 1;
        for (int i = 1; i <= n; ++i) {
            int prefix = 1 << (i - 1);
            for (int i = len - 1; i >= 0; i--)
                result.push_back(prefix | result[i]);
            len <<= 1;
        }
        return result;
    }
};

TEST_CASE("Gray Code - 2") {
    vector<int> output1{0, 1, 3, 2};
    vector<int> output2{0, 2, 3, 1};
    auto answer = Solution().grayCode(2);
    REQUIRE((answer == output1 || answer == output2));
}
